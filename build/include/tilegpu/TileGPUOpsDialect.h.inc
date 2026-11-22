/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Dialect Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TileGPUOps.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tilegpu {


class TileGPUDialect : public ::mlir::Dialect {
  explicit TileGPUDialect(::mlir::MLIRContext *context);

  void initialize();
  friend class ::mlir::MLIRContext;
public:
  ~TileGPUDialect() override;
  static constexpr ::llvm::StringLiteral getDialectNamespace() {
    return ::llvm::StringLiteral("tilegpu");
  }
};

} // namespace mlir::tilegpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tilegpu::TileGPUDialect)
