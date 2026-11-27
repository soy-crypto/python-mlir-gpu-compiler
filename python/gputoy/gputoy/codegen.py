"""Emit MLIR text from gputoy's static f32 Tensor graph."""


def emit_gemm(m, k, n, tile_size):
    """Emit the original TileGPU function for two input matrices."""
    if type(tile_size) is not int or tile_size <= 0:
        raise ValueError("tile_size must be a positive integer")
    if any(dim % tile_size for dim in (m, k, n)):
        raise ValueError(f"tile size {tile_size} must divide M={m}, K={k}, N={n}")
    a = f"memref<{m}x{k}xf32>"
    b = f"memref<{k}x{n}xf32>"
    c = f"memref<{m}x{n}xf32>"
    return f"""func.func @gemm(%A: {a}, %B: {b}, %C: {c}) {{
  "tilegpu.gemm"(%A, %B, %C) <{{tile = array<i64: {tile_size}, {tile_size}>, epilogue = "none"}}> : ({a}, {b}, {c}) -> ()
  return
}}"""


def dependency_order(result):
    """Visit a tensor after its inputs. Emit each tensor only once."""
    ordered = []
    seen = set()

    def visit(tensor):
        if tensor in seen:
            return
        for operand in tensor.inputs:
            visit(operand)
        seen.add(tensor)
        ordered.append(tensor)

    visit(result)
    return ordered


def memref_type(tensor):
    dimensions = "".join(f"{size}x" for size in tensor.shape)
    return f"memref<{dimensions}{tensor.dtype}>"


def emit_matmul(node, buffers, dest):
    a, b = node.inputs
    out_type = memref_type(node)
    return [
        f"  linalg.fill ins(%zero : f32) outs({dest} : {out_type})",
        f"  linalg.matmul ins({buffers[a]}, {buffers[b]} : {memref_type(a)}, {memref_type(b)})"
        f" outs({dest} : {out_type})",
    ]


IDENTITY = "affine_map<(i, j) -> (i, j)>"
COLUMN = "affine_map<(i, j) -> (j)>"


def emit_add_bias(node, buffers, dest):
    matrix, bias = node.inputs
    matrix_type = memref_type(matrix)
    return [
        "  linalg.generic {",
        f"    indexing_maps = [{IDENTITY}, {COLUMN}, {IDENTITY}],",
        '    iterator_types = ["parallel", "parallel"]',
        f"  }} ins({buffers[matrix]}, {buffers[bias]} : {matrix_type}, {memref_type(bias)})",
        f"    outs({dest} : {matrix_type}) {{",
        "  ^bb0(%x: f32, %b: f32, %old: f32):",
        "    %y = arith.addf %x, %b : f32",
        "    linalg.yield %y : f32",
        "  }",
    ]


def emit_relu(node, buffers, dest):
    (x,) = node.inputs
    ty = memref_type(x)
    axes = ", ".join(f"d{i}" for i in range(len(x.shape)))
    identity = f"affine_map<({axes}) -> ({axes})>"
    iterators = ", ".join(['"parallel"'] * len(x.shape))
    return [
        "  linalg.generic {",
        f"    indexing_maps = [{identity}, {identity}],",
        f"    iterator_types = [{iterators}]",
        f"  }} ins({buffers[x]} : {ty}) outs({dest} : {ty}) {{",
        "  ^bb0(%x: f32, %old: f32):",
        "    %y = arith.maximumf %x, %zero : f32",
        "    linalg.yield %y : f32",
        "  }",
    ]


def emit_ir(result, tile_size=None):
    """Emit a plain TileGPU GEMM or an unfused Linalg function for a graph.

    Graph arguments are inputs in first-use order, followed by a separate
    caller-provided output buffer. Tiling a Linalg graph is a later pass.
    """
    if result.op == "matmul":
        a, b = result.inputs
        if a.op == b.op == "input" and a is not b:
            m, k = a.shape
            return emit_gemm(m, k, b.shape[1], 8 if tile_size is None else tile_size)
    if tile_size is not None:
        raise ValueError("tile_size applies to the direct TileGPU GEMM example")

    ordered = dependency_order(result)
    inputs = [node for node in ordered if node.op == "input"]
    buffers = {node: f"%arg{i}" for i, node in enumerate(inputs)}
    args = [f"{buffers[node]}: {memref_type(node)}" for node in inputs]
    args.append(f"%out: {memref_type(result)}")
    lines = [f"func.func @forward({', '.join(args)}) {{"]
    lines.append("  %zero = arith.constant 0.0 : f32")

    emitters = {"matmul": emit_matmul, "add_bias": emit_add_bias, "relu": emit_relu}
    temporaries = []
    for node in ordered:
        if node.op == "input":
            continue
        if node.op not in emitters:
            raise ValueError(f"unsupported operation: {node.op}")
        if node is result:
            dest = "%out"
        else:
            dest = f"%tmp{len(temporaries)}"
            lines.append(f"  {dest} = memref.alloc() : {memref_type(node)}")
            temporaries.append((dest, memref_type(node)))
        lines.extend(emitters[node.op](node, buffers, dest))
        buffers[node] = dest

    if result.op == "input":
        ty = memref_type(result)
        lines.append(f"  memref.copy {buffers[result]}, %out : {ty} to {ty}")
    for dest, ty in temporaries:
        lines.append(f"  memref.dealloc {dest} : {ty}")
    lines.extend(["  return", "}"])
    return "\n".join(lines)
