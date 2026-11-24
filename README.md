Python DSL + IR design + GPU Lowering

# TileGPU — a Python-to-GPU compiler for GEMM

TileGPU compiles matrix multiplication from Python to an NVIDIA GPU through a custom MLIR operation, `tilegpu.gemm`. Changing the tile size in the input IR changes the GPU launch geometry and the amount of shared memory each block uses. The demo checks every output element against NumPy.

## Run the demo

From the repository root:

```bash
bash demo/run_gemm.sh
```

The script builds `tilegpu-opt`, emits a 64×64 float32 GEMM from Python, and compiles two kernels for an NVIDIA RTX A3000 Laptop GPU (`sm_86`). It runs the tiles in the order 8×8, 16×16, 16×16, 8×8. Each `PASS` means all 4,096 output elements matched `A @ B`.

The tested setup uses Linux, CMake, a C/C++ toolchain, Python 3 with NumPy, and an LLVM/MLIR build with the NVPTX backend and CUDA runtime (`libmlir_cuda_runtime.so`). The demo uses `/root/llvm-project/build`. If your LLVM build lives elsewhere, update the build path in `demo/run_gemm.sh` and the runtime path in `demo/benchmark_gemm.py`.

## What the IR expresses

`tilegpu.gemm` reads `A[M,K]` and `B[K,N]` and overwrites `C[M,N]`. All three operands are statically shaped, rank-2 float32 buffers. The `tile` attribute specifies how many output rows and columns one block computes. The current lowering uses square tiles that divide M, N, and K evenly. The demo uses `epilogue = "none"` for plain GEMM.

The Python example emits a rectangular case:

```mlir
func.func @gemm(%A: memref<16x32xf32>, %B: memref<32x8xf32>, %C: memref<16x8xf32>) {
  "tilegpu.gemm"(%A, %B, %C) <{tile = array<i64: 8, 8>, epilogue = "none"}>
    : (memref<16x32xf32>, memref<32x8xf32>, memref<16x8xf32>) -> ()
  return
}
```

After building the demo, inspect the lowering directly:

```bash
python3 examples/matmul.py |
  ./build/tilegpu-opt --pass-pipeline='builtin.module(tilegpu-to-gpu)' -
```

For this example, the launch has one block across the 8 output columns and two blocks down the 16 rows. Each thread owns one element of C. The block loads tiles of A and B into shared memory, synchronizes, and accumulates eight products per thread. A second barrier protects the tiles before the next load. After four K tiles, each thread writes its final sum once. This case matched NumPy on all 128 outputs.

## Benchmark

Measured on the RTX A3000 Laptop GPU for 64×64 float32 matrices. Each entry is the median of 100 synchronous calls from Python after 10 warmup calls. The time includes Python call and GPU launch overhead. Allocation, initialization, and the NumPy comparison happen outside the timer.

| Tile order | 8×8 tile (µs/call) | 16×16 tile (µs/call) |
| --- | ---: | ---: |
| 8×8, then 16×16 | 339.25 | 292.69 |
| 16×16, then 8×8 | 385.11 | 452.06 |

Both tiles cover the same output. The 8×8 version launches 64 blocks of 64 threads, and the 16×16 version launches 16 blocks of 256 threads. The lower median changed between runs, so these measurements do not establish a consistent winner.

## Where to read the code

| File | Role |
| --- | --- |
| [examples/matmul.py](examples/matmul.py) | Emits the matrix types, tile attribute, and GEMM operation from Python. |
| [include/tilegpu/TileGPUOps.td](include/tilegpu/TileGPUOps.td) | Defines the dialect and the operation's operands, attributes, and results. |
| [lib/TileGPU.cpp](lib/TileGPU.cpp) | Registers the operations and verifies GEMM shape and tile constraints. |
| [lib/TileGPUToGPU.cpp](lib/TileGPUToGPU.cpp) | Builds the launch, shared-memory tiles, barriers, and reduction loops. |
| [test/check_gemm_gpu.py](test/check_gemm_gpu.py) | Calls the compiled GEMM with GPU-accessible buffers and checks the output against NumPy. |
| [demo/benchmark_gemm.py](demo/benchmark_gemm.py) | Checks both square kernels and measures their call latency. |
