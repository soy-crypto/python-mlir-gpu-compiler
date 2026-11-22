#include "tilegpu/TileGPU.h"
#include "mlir/IR/BuiltinTypes.h"
#include "llvm/Support/Casting.h"

namespace mlir::tilegpu
{
    LogicalResult GemmOp::verify()
    {
        auto a = llvm::cast<MemRefType>(getLhs().getType);
        auto b = llvm::cast<MemRefType>(getRhs().getType);
        auto c = llvm::cast<MemRefType>(getOutput().getType())
    }

} // namespace mlir::tilegpu