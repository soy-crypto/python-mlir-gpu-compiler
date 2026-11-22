/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TileGPUOps.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::TileGPUDialect)
namespace mlir::tilegpu {


TileGPUDialect::TileGPUDialect(::mlir::MLIRContext *context)
    : ::mlir::Dialect(getDialectNamespace(), context, ::mlir::TypeID::get<TileGPUDialect>())
    
     {
  
  initialize();
}

TileGPUDialect::~TileGPUDialect() = default;


} // namespace mlir::tilegpu
