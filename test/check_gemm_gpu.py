import ctypes as ct
from contextlib import ExitStack
import sys

import numpy as np

cuda = ct.CDLL("/root/llvm-project/build/lib/libmlir_cuda_runtime.so")
cuda.mgpuMemAlloc.argtypes = [ct.c_uint64, ct.c_void_p, ct.c_bool]
cuda.mgpuMemAlloc.restype = ct.c_void_p
cuda.mgpuMemFree.argtypes = [ct.c_void_p, ct.c_void_p]
cuda.mgpuMemFree.restype = None


tile = int(sys.argv[1]) if len(sys.argv) > 1 else 16
gemm = ct.CDLL("./build/libgemm_rect.so").gemm
matrix_args = [ct.c_void_p, ct.c_void_p] + [ct.c_int64] * 5
gemm.argtypes = matrix_args * 3
gemm.restype = None
    



def make_matrix(cleanup: ExitStack, rows: int = 64, cols: int = 64):
    storage = ct.c_float * (rows * cols)
    ptr = cuda.mgpuMemAlloc(ct.sizeof(storage), None, True)
    if not ptr:
        raise MemoryError("GPU allocation failed")
    cleanup.callback(cuda.mgpuMemFree, ptr, None)

    matrix = np.ctypeslib.as_array(storage.from_address(ptr)).reshape(rows, cols)
    return matrix, (ptr, ptr, 0, rows, cols, cols, 1)


with ExitStack() as cleanup:
    A, a_args = make_matrix(cleanup, 16, 32)
    B, b_args = make_matrix(cleanup, 32, 8)
    C, c_args = make_matrix(cleanup, 16, 8)

    rng = np.random.default_rng(0)
    A[:] = rng.integers(-3, 4, size=A.shape)
    B[:] = rng.integers(-3, 4, size=B.shape)
    C.fill(5)
    expected = A @ B

    gemm(*a_args, *b_args, *c_args)
    np.testing.assert_array_equal(C, expected)
    print(f"PASS: {tile}x{tile} tile, all 4096 outputs match NumPy")
    
    assert C.shape == (16, 8)
    np.testing.assert_array_equal(C, expected)
    print(f"PASS: C{C.shape}, all {C.size} outputs match NumPy")