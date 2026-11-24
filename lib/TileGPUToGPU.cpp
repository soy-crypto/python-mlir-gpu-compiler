#include "tilegpu/Passes.h"
#include "tilegpu/TileGPU.h"

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/Support/Casting.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/IR/Builders.h"

namespace mlir::tilegpu
{
    namespace
    {
        void lowerGemm(GemmOp op)
        {
            // get op atrr and tile
            auto cType = llvm::cast<MemRefType>(op.getOutput().getType());
            auto tile  = op.getTileAttr().asArrayRef();
            int64_t rows     = cType.getDimSize(0);
            int64_t cols     = cType.getDimSize(1);
            int64_t tileRows = tile[0];
            int64_t tileCols = tile[1];
            int64_t gridX    = cols / tileCols;
            int64_t gridY    = rows / tileRows;

            // gpu launch implementation
            /** launch head */
            OpBuilder builder(op.getOperation());
            Location loc = op.getLoc();
            auto index = [&](int64_t n) -> Value
            {
                return builder.create<arith::ConstantIndexOp>(loc, n);
            };


            Value gx    = index(gridX);
            Value gy    = index(gridY);
            Value bx    = index(tileCols);
            Value by    = index(tileRows);
            Value one   = index(1);
            auto launch = builder.create<gpu::LaunchOp>(loc, gx, gy, one, bx, by, one);
            builder.setInsertionPointToStart(&launch.getBody().front());
            
            /* launch body */
            auto block  = launch.getBlockIds();
            auto thread = launch.getThreadIds();
            auto size   = launch.getBlockSize();

            Value firstRow = builder.create<arith::MulIOp>(loc, block.y, size.y);
            Value row      = builder.create<arith::AddIOp>(loc, firstRow, thread.y);
            Value firstCol = builder.create<arith::MulIOp>(loc, block.x, size.x);
            Value col      = builder.create<arith::AddIOp>(loc, firstCol, thread.x);

            /** k tiles loop */

            
            

            /** terminator */
            builder.create<gpu::TerminatorOp>(loc);

            //return
            return;

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

            void getDependentDialects(DialectRegistry& registry) const override
            {
                registry.insert<arith::ArithDialect, gpu::GPUDialect>();
            }

        };

    } // namespace

    void registerTileGPUToGPUPass()
    {
        PassRegistration<TileGPUToGPUPass>{};
    }

};