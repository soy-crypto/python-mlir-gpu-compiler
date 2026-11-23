func.func @bad_inner_dims(%A:memref<16x32xf32>, %B:memref<64x8xf32>, %C: memref<16x8xf32>)
{
    // expected-error @+1 {{requires A columns to equal B rows}}
    "tilegpu.gemm"(%A, %B, %C) <{tile = array<i64: 8, 8>, epilogue = "none"}> : (memref<16x32xf32>, memref<64x8xf32>, memref<16x8xf32>) -> ()

    return
}