def emit_gemm(m: int, k: int, n: int, tile_size: int) -> str:
    a_type = f"memref<{m}x{k}xf32>"
    b_type = f"memref<{k}x{n}xf32>"
    c_type = f"memref<{m}x{n}xf32>"
    
    return f"""
            func.func @gemm(%A: {a_type}, %B: {b_type}, %C:{c_type})
            {{
                "tilegpu.gemm"(%A, %B, %C) <{{tile = array<i64: {tile_size}, {tile_size}>, epilogue = "none"}}> : ({a_type}, {b_type}, {c_type}) -> ()
                return 
            }}"""

if __name__ == "__main__":
    print(emit_gemm(16, 32, 8, 8))