GEMM:
input A[64, 64] B[64, 64]
output C[64, 64]

for output element C[i, j], tilegpu.gemm computes the dot product of row i of A and column j of B. It overwrites the previous value of C[i, j] with that result.