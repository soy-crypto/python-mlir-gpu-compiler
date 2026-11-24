#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."
export PATH="/usr/bin:/bin:$PATH"
llvm_build=/root/llvm-project/build

cmake --build build --target tilegpu-opt

for tile in 8 16; do
  sed "s/array<i64: 8, 8>/array<i64: $tile, $tile>/" examples/gemm.mlir |
    ./build/tilegpu-opt --pass-pipeline='builtin.module(tilegpu-to-gpu)' - |
    "$llvm_build/bin/mlir-opt" \
      --gpu-lower-to-nvvm-pipeline='cubin-chip=sm_86 cubin-features=+ptx71' |
    "$llvm_build/bin/mlir-translate" --mlir-to-llvmir |
    "$llvm_build/bin/llc" -filetype=obj -relocation-model=pic \
      -o "build/gemm${tile}.o"

  cc -shared "build/gemm${tile}.o" -L"$llvm_build/lib" \
    -Wl,-rpath,"$llvm_build/lib" -Wl,-z,defs -lmlir_cuda_runtime \
    -o "build/libgemm${tile}.so"

  python3 test/check_gemm_gpu.py "$tile"
done