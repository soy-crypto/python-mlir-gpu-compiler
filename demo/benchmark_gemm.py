import ctypes as ct
from contextlib import ExitStack
from pathlib import Path
from statistics import median
from time import perf_counter_ns

import numpy as np


BUILD_DIR = Path(__file__).resolve().parents[1] / "build"
CUDA_RUNTIME = "/root/llvm-project/build/lib/libmlir_cuda_runtime.so"


def make_matrix(cuda, cleanup, rows, cols):
    storage = ct.c_float * (rows * cols)
    ptr = cuda.mgpuMemAlloc(ct.sizeof(storage), None, True)
    if not ptr:
        raise MemoryError("GPU allocation failed")
    cleanup.callback(cuda.mgpuMemFree, ptr, None)

    matrix = np.ctypeslib.as_array(storage.from_address(ptr)).reshape(rows, cols)

    # Allocated pointer, aligned pointer, offset, sizes, strides.
    args = (ptr, ptr, 0, rows, cols, cols, 1)
    return matrix, args


def median_call_us(run, warmup=10, repeats=100):
    for _ in range(warmup):
        run()

    samples = []
    for _ in range(repeats):
        start = perf_counter_ns()
        run()
        samples.append(perf_counter_ns() - start)

    return median(samples) / 1_000


def main():
    cuda = ct.CDLL(CUDA_RUNTIME)
    cuda.mgpuMemAlloc.argtypes = [ct.c_uint64, ct.c_void_p, ct.c_bool]
    cuda.mgpuMemAlloc.restype = ct.c_void_p
    cuda.mgpuMemFree.argtypes = [ct.c_void_p, ct.c_void_p]
    cuda.mgpuMemFree.restype = None

    matrix_argtypes = [ct.c_void_p, ct.c_void_p] + [ct.c_int64] * 5

    with ExitStack() as cleanup:
        A, a_args = make_matrix(cuda, cleanup, 64, 64)
        B, b_args = make_matrix(cuda, cleanup, 64, 64)
        C, c_args = make_matrix(cuda, cleanup, 64, 64)
        args = (*a_args, *b_args, *c_args)

        rng = np.random.default_rng(0)
        A[:] = rng.integers(-3, 4, size=A.shape)
        B[:] = rng.integers(-3, 4, size=B.shape)
        expected = A @ B

        for tile in (8, 16):
            lib = ct.CDLL(str(BUILD_DIR / f"libgemm{tile}.so"))
            gemm = lib.gemm
            gemm.argtypes = matrix_argtypes * 3
            gemm.restype = None

            C.fill(5)
            gemm(*args)
            np.testing.assert_array_equal(C, expected)

            elapsed_us = median_call_us(lambda: gemm(*args))
            print(f"PASS | {tile}×{tile} tile | median {elapsed_us:.2f} µs/call")


if __name__ == "__main__":
    main()