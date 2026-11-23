#include "tilegpu/Passes.h"
#include "tilegpu/TileGPU.h"

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/Support/Casting.h"

namespace mlir::tilegpu
{
    namespace
    {
        void lowerGemm(GemmOp op)
        {
            // get atrr anbd tile
            auto cType = llvm::cast<MemRefType>(op.getOutput().getType());
            auto tile = op.getTileAttr().asArrayRef();

            int64_t rows = cType.getDimSize(0);
            int64_t cols = cType.getDimSize(1);
            int64_t tileRows = tile[0];
            int64_t tileCols = tile[1];

            // grid size
            int64_t gridX = cols / tileCols;
            int64_t gridY = rows / tileRows;

            //
            op.emitRemark() << "grid=(" << gridX << "," << gridY << "), block=(" << tileCols << "," << tileRows << ")";
        }

        struct TileGPUToGPUPass : PassWrapper<TileGPUToGPUPass, OperationPass<ModuleOp>>
        {
            MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(TileGPUToGPUPass);

            StringRef getArgument() const final
            {
                return "tilegpu-to-gpu";
            }

            void runOnOperation() final
            {
                getOperation().walk([](GemmOp op)
                { 
                    lowerGemm(op); 
                }
                );
            }
        };

    } // namespace

    void registryTileGPUToGPUPass()
    {
        PassRegistration<TileGPUToGPUPass>{};
    }

};