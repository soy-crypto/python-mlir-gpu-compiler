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
        addOperations<GemmOp, ReluOp, AddOp>();
    }

    LogicalResult GemmOp::verify()
    {
        // get opereands
        auto a = llvm::cast<MemRefType>(getLhs().getType());
        auto b = llvm::cast<MemRefType>(getRhs().getType());
        auto c = llvm::cast<MemRefType>(getOutput().getType());
        auto epilogue = getEpilogue();
        auto bias = getBias();

        // parameters checking
        /** dimentions checking */
        if (a.getRank() != 2 || b.getRank() != 2 || c.getRank() != 2)
        {
            return emitOpError("requires A, B, and C to be rank-2 matrices");
        }

        /** shape checking */
        if (!a.hasStaticShape() || !b.hasStaticShape() || !c.hasStaticShape())
        {
            return emitOpError("requires statically known matrix dimensions");
        }

        /** A[, k] and B[k, ]column checking */
        if (a.getDimSize(1) != b.getDimSize(0))
        {
            return emitOpError(" requires A columns to equal B rows");
        }

        /** C[i, j] and A[i, ] and B[, j] */
        if (c.getDimSize(0) != a.getDimSize(0) || c.getDimSize(1) != b.getDimSize(1))
        {
            return emitOpError("requires C to have A's rows and B's columns");
        }

        // attributes checking
        auto tile = getTileAttr().asArrayRef();
        if (tile.size() != 2)
        {
            return emitOpError("requires two tile dimesions: rows and columns");
        }

        if (tile[0] <= 0 || tile[1] <= 0)
        {
            return emitOpError("requires positive tile dimenstions");
        }

        if (c.getDimSize(0) % tile[0] != 0 || c.getDimSize(1) % tile[1] != 0)
        {
            return emitOpError("requires tile dimension to divide the output dimensions");
        }

        // epilogue checking
        if (epilogue == "none")
        {
            if(bias)
            {
                return emitOpError("plain GEMM expects only A, B, and C");
            }
        }
        else
        {
            
        }

        // return
        return success();
    }

} // namespace mlir::tilegpu