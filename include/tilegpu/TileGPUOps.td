include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

//define dialect
def TileGPU_Dialect : Dialect 
{
    let name = "tilegpu";
    let cppNamespace = "::mlir::tilegpu";
}

//define Ops
/** GemmOp */
def TileGPU_GemmOp : Op<TileGPU_Dialect, "gemm">
{
    let summary = "overwrite C with the matrix product of A and B";
    let arguments = (ins 
                        Arg<F32MemRef, "left matrix",   [MemRead]>  : $lhs, 
                        Arg<F32MemRef, "right matrix",  [MemRead]>  : $rhs, 
                        Arg<F32MemRef, "output matrix", [MemWrite]> : $output,
                        DenseI64ArrayAttr : $tile,
                        StrAttr : $epilogues
                    );

    let results = (outs);
    let hasVerifier = 1;
}

/** ReluOp */
define TileGPU_ReluOp : Op<TileGPU_Dialect, "relu">
{
    let summary = "write max(input, 0) elementwise into output";
    let argument = (ins  
                        Arg<F32MemRef, "input",  [MemRead]>  : $input, 
                        Arg<F32MemRef, "output", [MemWrite]> : $output, 
                        DenseI64ArrayAttr : $tile
                    );

    let results = (outs);
}