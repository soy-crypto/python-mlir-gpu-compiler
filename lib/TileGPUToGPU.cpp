#include "tilegpu/Passes.h"
#include "tilegpu/TileGPU.h"

#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm/Support/Casting.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/GPU/IR/GPUDialect.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"

#include "mlir/IR/Builders.h"

namespace mlir::tilegpu
{
    namespace
    {
        void lowerGemm(GemmOp op)
        {
            // get op atrr and tile
            Value A = op.getLhs();
            Value B = op.getRhs();
            Value C = op.getOutput();
            auto tile  = op.getTileAttr().asArrayRef();
            auto AType = llvm::cast<MemRefType>(op.getLhs().getType());
            auto BType = llvm::cast<MemRefType>(op.getRhs().getType());
            auto CType = llvm::cast<MemRefType>(op.getOutput().getType());

            int64_t rows     = CType.getDimSize(0);
            int64_t cols     = CType.getDimSize(1);
            int64_t tileRows = tile[0];
            int64_t tileCols = tile[1];
            int64_t gridRows = rows / tileRows;
            int64_t gridCols = cols / tileCols;

            // gpu launch implementation
            /** launch head */
            OpBuilder builder(op.getOperation());
            Location loc = op.getLoc();
            auto index = [&](int64_t n) -> Value { return builder.create<arith::ConstantIndexOp>(loc, n); };
            Value gRows = index(gridRows);
            Value gCols = index(gridCols);
            Value bRows = index(tileRows);
            Value bCols = index(tileCols);
            Value one   = index(1);
            auto space    = gpu::AddressSpaceAttr::get(builder.getContext(), gpu::AddressSpace::Workgroup);
            auto tileType = MemRefType::get({tileRows, tileCols}, builder.getF32Type(), MemRefLayoutAttrInterface{}, space);

            auto launch = builder.create<gpu::LaunchOp>(loc, gCols, gRows, one, bCols, bRows, one);
            Value ATile = launch.addWorkgroupAttribution(tileType, loc);
            Value BTile = launch.addWorkgroupAttribution(tileType, loc);
            builder.setInsertionPointToStart(&launch.getBody().front());
            
            /* launch entry */
            auto block    = launch.getBlockIds();
            auto thread   = launch.getThreadIds();
            auto tileSize = launch.getBlockSize();

            Value firstRow = builder.create<arith::MulIOp>(loc, block.y,  tileSize.y);
            Value row      = builder.create<arith::AddIOp>(loc, firstRow, thread.y);
            Value firstCol = builder.create<arith::MulIOp>(loc, block.x,  tileSize.x);
            Value col      = builder.create<arith::AddIOp>(loc, firstCol, thread.x);
            Value start = index(0);
            Value end   = index(AType.getDimSize(1));
            Value step  = index(tileCols);

            /** k tile head */
            Value zero  = builder.create<arith::ConstantOp>(loc, builder.getF32FloatAttr(0.0));
            auto kLoopOp  = builder.create<scf::ForOp>(loc, start, end, step, ValueRange{zero});
            builder.setInsertionPointToStart(kLoopOp.getBody());
            
            /** k tile body */
            Value k = kLoopOp.getInductionVar();
            Value i = builder.create<arith::AddIOp>(loc, k, thread.y);
            Value j = builder.create<arith::AddIOp>(loc, k, thread.x);
            Value aVal = builder.create<memref::LoadOp>(loc, A, ValueRange{row, j});
            Value bVal = builder.create<memref::LoadOp>(loc, B, ValueRange{i, col});
            builder.create<memref::StoreOp>(loc, aVal, ATile, ValueRange{thread.y, thread.x});
            builder.create<memref::StoreOp>(loc, bVal, BTile, ValueRange{thread.y, thread.x});
            /** wait for aTile and bTile population done */
            builder.create<gpu::BarrierOp>(loc);

            /** productSum loop */
            auto loopOp = builder.create<scf::ForOp>(loc, start, tileSize.x, one, ValueRange{kLoopOp.getRegionIterArgs()[0]});
            builder.setInsertionPointToStart(loopOp.getBody());
            Value a = builder.create<memref::LoadOp>(loc, ATile, ValueRange{thread.y, loopOp.getInductionVar()});
            Value b = builder.create<memref::LoadOp>(loc, BTile, ValueRange{loopOp.getInductionVar(), thread.x});
            Value product = builder.create<arith::MulFOp>(loc, a, b);
            Value sum = builder.create<arith::AddFOp>(loc, product, loopOp.getRegionIterArgs()[0]);
            builder.create<scf::YieldOp>(loc, sum);
            builder.setInsertionPointAfter(loopOp);
            
            /** wait for ps loop done */
            builder.create<gpu::BarrierOp>(loc);

            /** outside productSum loop */
            builder.create<scf::YieldOp>(loc, loopOp.getResult(0));
            builder.setInsertionPointAfter(kLoopOp);

            /** wait for ps Kloop done */
            builder.create<gpu::BarrierOp>(loc);

            /** outside k loop */
            builder.create<memref::StoreOp>(loc, kLoopOp.getResult(0), C, ValueRange{row, col});

            /** wait for C[row, col] done */
            builder.create<gpu::BarrierOp>(loc);

            /** terminate launch */
            builder.create<gpu::TerminatorOp>(loc);

           //erase op
           op.erase();

           //return
           return;
        }
        
        //pass
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
                registry.insert<arith::ArithDialect, gpu::GPUDialect, scf::SCFDialect, memref::MemRefDialect>();
            }

        };

    } // namespace

    void registerTileGPUToGPUPass()
    {
        PassRegistration<TileGPUToGPUPass>{};
    }

};