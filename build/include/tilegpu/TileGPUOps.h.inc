/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Declarations                                                            *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TileGPUOps.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace mlir::tilegpu {

/// overwrite C with the matrix product of A and B
class GemmOp;

} // namespace mlir::tilegpu
#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES

namespace mlir::tilegpu {


//===----------------------------------------------------------------------===//
// ::mlir::tilegpu::GemmOp declarations
//===----------------------------------------------------------------------===//

namespace detail {

class GemmOpGenericAdaptorBase {
public:
  struct Properties {
    using epiloguesTy = ::mlir::StringAttr;
    epiloguesTy epilogues;

    auto getEpilogues() const {
      auto &propStorage = this->epilogues;
      return ::llvm::cast<::mlir::StringAttr>(propStorage);
    }
    void setEpilogues(const ::mlir::StringAttr &propValue) {
      this->epilogues = propValue;
    }
    using tileTy = ::mlir::DenseI64ArrayAttr;
    tileTy tile;

    auto getTile() const {
      auto &propStorage = this->tile;
      return ::llvm::cast<::mlir::DenseI64ArrayAttr>(propStorage);
    }
    void setTile(const ::mlir::DenseI64ArrayAttr &propValue) {
      this->tile = propValue;
    }
    bool operator==(const Properties &rhs) const {
      return 
        rhs.epilogues == this->epilogues &&
        rhs.tile == this->tile &&
        true;
    }
    bool operator!=(const Properties &rhs) const {
      return !(*this == rhs);
    }
  };
protected:
  ::mlir::DictionaryAttr odsAttrs;
  ::std::optional<::mlir::OperationName> odsOpName;
  Properties properties;
  ::mlir::RegionRange odsRegions;
public:
  GemmOpGenericAdaptorBase(::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : odsAttrs(attrs), properties(properties), odsRegions(regions) {  if (odsAttrs)
      odsOpName.emplace("tilegpu.gemm", odsAttrs.getContext());
  }

  GemmOpGenericAdaptorBase(GemmOp op);

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index, unsigned odsOperandsSize) {
    return {index, 1};
  }

  const Properties &getProperties() {
    return properties;
  }

  ::mlir::DictionaryAttr getAttributes() {
    return odsAttrs;
  }

  ::mlir::DenseI64ArrayAttr getTileAttr() {
    auto attr = ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().tile);
    return attr;
  }

  ::llvm::ArrayRef<int64_t> getTile();
  ::mlir::StringAttr getEpiloguesAttr() {
    auto attr = ::llvm::cast<::mlir::StringAttr>(getProperties().epilogues);
    return attr;
  }

  ::llvm::StringRef getEpilogues();
};

} // namespace detail
template <typename RangeT>
class GemmOpGenericAdaptor : public detail::GemmOpGenericAdaptorBase {
  using ValueT = ::llvm::detail::ValueOfRange<RangeT>;
  using Base = detail::GemmOpGenericAdaptorBase;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_output = 2;
public:
  GemmOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, const Properties &properties, ::mlir::RegionRange regions = {}) : Base(attrs, properties, regions), odsOperands(values) {}

  GemmOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs, ::mlir::PropertyRef properties, ::mlir::RegionRange regions = {}) : GemmOpGenericAdaptor(values, attrs, (properties ? *properties.as<Properties *>() : Properties{}), regions) {}

  GemmOpGenericAdaptor(RangeT values, ::mlir::DictionaryAttr attrs = nullptr) : GemmOpGenericAdaptor(values, attrs, Properties{}, {}) {}

  GemmOpGenericAdaptor(RangeT values, const GemmOpGenericAdaptorBase &base) : Base(base), odsOperands(values) {}

  template <typename LateInst = GemmOp, typename = std::enable_if_t<std::is_same_v<LateInst, GemmOp>>>
  GemmOpGenericAdaptor(RangeT values, LateInst op) : Base(op), odsOperands(values) {}

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return Base::getODSOperandIndexAndLength(index, odsOperands.size());
  }

  RangeT getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(odsOperands.begin(), valueRange.first),
             std::next(odsOperands.begin(), valueRange.first + valueRange.second)};
  }

  ValueT getLhs() {
    return (*getODSOperands(0).begin());
  }

  ValueT getRhs() {
    return (*getODSOperands(1).begin());
  }

  ValueT getOutput() {
    return (*getODSOperands(2).begin());
  }

  RangeT getOperands() {
    return odsOperands;
  }

private:
  RangeT odsOperands;
};
class GemmOpAdaptor : public GemmOpGenericAdaptor<::mlir::ValueRange> {
public:
  using GemmOpGenericAdaptor::GemmOpGenericAdaptor;
  GemmOpAdaptor(GemmOp op);

  ::llvm::LogicalResult verify(::mlir::Location loc);
};
class GemmOp : public ::mlir::Op<GemmOp, ::mlir::OpTrait::ZeroRegions, ::mlir::OpTrait::ZeroResults, ::mlir::OpTrait::ZeroSuccessors, ::mlir::OpTrait::NOperands<3>::Impl, ::mlir::OpTrait::OpInvariants, ::mlir::BytecodeOpInterface::Trait, ::mlir::MemoryEffectOpInterface::Trait> {
public:
  using Op::Op;
  using Op::print;
  using Adaptor = GemmOpAdaptor;
  template <typename RangeT>
  using GenericAdaptor = GemmOpGenericAdaptor<RangeT>;
  using FoldAdaptor = GenericAdaptor<::llvm::ArrayRef<::mlir::Attribute>>;
  static constexpr int odsIndex_lhs = 0;
  static constexpr int odsIndex_rhs = 1;
  static constexpr int odsIndex_output = 2;
  using Properties = FoldAdaptor::Properties;
  static ::llvm::ArrayRef<::llvm::StringRef> getAttributeNames() {
    static ::llvm::StringRef attrNames[] = {::llvm::StringRef("epilogues"), ::llvm::StringRef("tile")};
    return ::llvm::ArrayRef(attrNames);
  }

  ::mlir::StringAttr getEpiloguesAttrName() {
    return getAttributeNameForIndex(0);
  }

  static ::mlir::StringAttr getEpiloguesAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 0);
  }

  ::mlir::StringAttr getTileAttrName() {
    return getAttributeNameForIndex(1);
  }

  static ::mlir::StringAttr getTileAttrName(::mlir::OperationName name) {
    return getAttributeNameForIndex(name, 1);
  }

  static constexpr ::llvm::StringLiteral getOperationName() {
    return ::llvm::StringLiteral("tilegpu.gemm");
  }

  std::pair<unsigned, unsigned> getODSOperandIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::operand_range getODSOperands(unsigned index) {
    auto valueRange = getODSOperandIndexAndLength(index);
    return {std::next(getOperation()->operand_begin(), valueRange.first),
             std::next(getOperation()->operand_begin(), valueRange.first + valueRange.second)};
  }

  ::mlir::TypedValue<::mlir::MemRefType> getLhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(0).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getRhs() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(1).begin());
  }

  ::mlir::TypedValue<::mlir::MemRefType> getOutput() {
    return ::llvm::cast<::mlir::TypedValue<::mlir::MemRefType>>(*getODSOperands(2).begin());
  }

  ::mlir::OpOperand &getLhsMutable() {
    auto range = getODSOperandIndexAndLength(0);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getRhsMutable() {
    auto range = getODSOperandIndexAndLength(1);
    return getOperation()->getOpOperand(range.first);
  }

  ::mlir::OpOperand &getOutputMutable() {
    auto range = getODSOperandIndexAndLength(2);
    return getOperation()->getOpOperand(range.first);
  }

  std::pair<unsigned, unsigned> getODSResultIndexAndLength(unsigned index) {
    return {index, 1};
  }

  ::mlir::Operation::result_range getODSResults(unsigned index) {
    auto valueRange = getODSResultIndexAndLength(index);
    return {std::next(getOperation()->result_begin(), valueRange.first),
             std::next(getOperation()->result_begin(), valueRange.first + valueRange.second)};
  }

  static ::llvm::LogicalResult setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::mlir::Attribute getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop);
  static llvm::hash_code computePropertiesHash(const Properties &prop);
  static std::optional<mlir::Attribute> getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name);
  static void setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value);
  static void walkInherentAttrs(::mlir::MLIRContext *ctx, Properties &prop, ::llvm::function_ref<void(::llvm::StringRef, ::mlir::Attribute &)> visitor);
  static ::llvm::LogicalResult verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  static ::llvm::LogicalResult readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state);
  void writeProperties(::mlir::DialectBytecodeWriter &writer);
  ::mlir::DenseI64ArrayAttr getTileAttr() {
    return ::llvm::cast<::mlir::DenseI64ArrayAttr>(getProperties().tile);
  }

  ::llvm::ArrayRef<int64_t> getTile();
  ::mlir::StringAttr getEpiloguesAttr() {
    return ::llvm::cast<::mlir::StringAttr>(getProperties().epilogues);
  }

  ::llvm::StringRef getEpilogues();
  void setTileAttr(::mlir::DenseI64ArrayAttr attr) {
    getProperties().tile = attr;
  }

  void setTile(::llvm::ArrayRef<int64_t> attrValue);
  void setEpiloguesAttr(::mlir::StringAttr attr) {
    getProperties().epilogues = attr;
  }

  void setEpilogues(::llvm::StringRef attrValue);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static void build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues);
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes = {});
  static void build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GemmOp create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  static GemmOp create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes = {});
  ::llvm::LogicalResult verifyInvariantsImpl();
  ::llvm::LogicalResult verifyInvariants();
  ::llvm::LogicalResult verify();
  static ::llvm::LogicalResult setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError);
  void getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects);
private:
  ::mlir::StringAttr getAttributeNameForIndex(unsigned index) {
    return getAttributeNameForIndex((*this)->getName(), index);
  }

  static ::mlir::StringAttr getAttributeNameForIndex(::mlir::OperationName name, unsigned index) {
    assert(index < 2 && "invalid attribute index");
    assert(name.getStringRef() == getOperationName() && "invalid operation name");
    assert(name.isRegistered() && "Operation isn't registered, missing a "
          "dependent dialect loading?");
    return name.getAttributeNames()[index];
  }

public:
};

} // namespace mlir::tilegpu
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tilegpu::GemmOp)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::mlir::tilegpu::detail::GemmOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

