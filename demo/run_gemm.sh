#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."
llvm_build=/root/llvm-project/build

cmake -S . -B build -DMLIR_DIR="$llvm_build/lib/cmake/mlir"
cmake --build build --target tilegpu-opt

for tile in 8 16; do
    base="build/gemm${tile}"

    PYTHONPATH=examples python3 - "$tile" > "$base.mlir" <<'PY'
import sys
from matmul import emit_gemm

tile = int(sys.argv[1])
print(emit_gemm(64, 64, 64, tile))
PY

    ./build/tilegpu-opt \
        --pass-pipeline='builtin.module(tilegpu-to-gpu)' "$base.mlir" |
        "$llvm_build/bin/mlir-opt" \
            --gpu-lower-to-nvvm-pipeline='cubin-chip=sm_86 cubin-features=+ptx71' \
            -o "$base-nvvm.mlir"

    "$llvm_build/bin/mlir-translate" --mlir-to-llvmir \
        "$base-nvvm.mlir" -o "$base.ll"

    "$llvm_build/bin/llc" -filetype=obj -relocation-model=pic \
        "$base.ll" -o "$base.o"

    cc -shared "$base.o" -L"$llvm_build/lib" \
        -Wl,-rpath,"$llvm_build/lib" -Wl,-z,defs \
        -lmlir_cuda_runtime -o "build/libgemm${tile}.so"
done

python3 demo/benchmark_gemm.py