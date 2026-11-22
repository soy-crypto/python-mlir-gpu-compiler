#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "llvm/Support/Casting.h"

#include "tilegpu/TileGPU.h"
#include "tilegpu/TileGPUOpsDialect.cpp.inc"
#define GET_OP_CLASSES
#include "tilegpu/TileGPUOps.cpp.inc"

namespace mlir::tilegpu
{
    void TileGPUDialect::initialize()
    {
        addOperations<GemmOp>();
    }

    LogicalResult GemmOp::verify()
    {
        // get opereands
        auto a = llvm::cast<MemRefType>(getLhs().getType());
        auto b = llvm::cast<MemRefType>(getRhs().getType());
        auto c = llvm::cast<MemRefType>(getOutput().getType());

        // dimension checking
        if (a.getRank() != 2 || b.getRank() != 2 || c.getRand() != 2)
        {
            mlir::MemRef
        }
    }

} // namespace mlir::tilegpu