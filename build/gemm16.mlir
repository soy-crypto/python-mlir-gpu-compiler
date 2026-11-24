
            func.func @gemm(%A: memref<64x64xf32>, %B: memref<64x64xf32>, %C:memref<64x64xf32>)
            {
                "tilegpu.gemm"(%A, %B, %C) <{tile = array<i64: 16, 16>, epilogue = "none"}> : (memref<64x64xf32>, memref<64x64xf32>, memref<64x64xf32>) -> ()
                return 
            }
