include "mlir/IR/OpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

//define dialect
def TileGPU_Dialect : Dialect 
{
    let name = "tilegpu";
    let cppNamespace = "::mlir::tilegpu";
}

//define GemmOp
def TileGPU_GemmOp : Op<TileGPU_Dialect, "gemm">
{
    let summary = "overwrite C with the matrix product of A and B";

    let arguments = (ins

    //operands
    Arg<F32MemRef, "left matrix",   [MemRead]>  : $lhs,
    Arg<F32MemRef, "right matrix",  [MemRead]>  : $rhs,
    Arg<F32MemRef, "output matrix", [MemWrite]> : $output,

    //attributes
    DenseI64ArrayAttr : $tile,
    StrAttr : $epilogues

    );

    //output
    let results = (outs);

    //Declare the custom verifier
    let hasVerifier = 1;

}