import ctypes as ct
from contextlib import ExitStack

import numpy as np

cuda = ct.CDLL("/root/llvm-project/build/lib/libmlir_cuda_runtime.so")
cuda.mgpuMemAlloc.argtypes = [ct.c_uint64, ct.c_void_p, ct.c_bool]
cuda.mgpuMemAlloc.restype = ct.c_void_p
cuda.mgpuMemFree.argtypes = [ct.c_void_p, ct.c_void_p]
cuda.mgpuMemFree.restype = None

gemm = ct.CDLL("./build/libgemm16.so").gemm
matrix_args = [ct.c_void_p, ct.c_void_p] + [ct.c_int64] * 5
gemm.argtypes = matrix_args * 3
gemm.restype = None

def make_matrix(cleanup):
    storage = ct.c_float * (64 * 64)
    ptr = cuda.mgpuMemAlloc(ct.sizeof(storage), None, True)
    if not ptr:
        raise MemoryError("GPU allocation failed")
    cleanup.callback(cuda.mgpuMemFree, ptr, None)

    matrix = np.ctypeslib.as_array(storage.from_address(ptr)).reshape(64, 64)
    return matrix, (ptr, ptr, 0, 64, 64, 64, 1)


with ExitStack() as cleanup:
    A, a_args = make_matrix(cleanup)
    B, b_args = make_matrix(cleanup)
    C, c_args = make_matrix(cleanup)

    rng = np.random.default_rng(0)
    A[:] = rng.integers(-3, 4, size=A.shape)
    B[:] = rng.integers(-3, 4, size=B.shape)
    C.fill(5)
    expected = A @ B

    gemm(*a_args, *b_args, *c_args)
    np.testing.assert_array_equal(C, expected)
    print("PASS: 16x16 tile, all 4096 outputs match NumPy")