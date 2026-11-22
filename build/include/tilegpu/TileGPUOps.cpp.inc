/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Op Definitions                                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|* From: TileGPUOps.td                                                        *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_OP_LIST
#undef GET_OP_LIST

::mlir::tilegpu::AddOp,
::mlir::tilegpu::GemmOp,
::mlir::tilegpu::ReluOp
#endif // GET_OP_LIST

#ifdef GET_OP_CLASSES
#undef GET_OP_CLASSES


//===----------------------------------------------------------------------===//
// Local Utility Method Definitions
//===----------------------------------------------------------------------===//


static ::llvm::LogicalResult __mlir_ods_local_type_constraint_TileGPUOps1(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!((type.isF32()))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be 32-bit float, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_type_constraint_TileGPUOps2(
    ::mlir::Operation *op, ::mlir::Type type, ::llvm::StringRef valueKind,
    unsigned valueIndex) {
  if (!(((::llvm::isa<::mlir::MemRefType>(type))) && ([](::mlir::Type elementType) { return (elementType.isF32()); }(::llvm::cast<::mlir::ShapedType>(type).getElementType())))) {
    return op->emitOpError(valueKind) << " #" << valueIndex
        << " must be memref of 32-bit float values, but got " << type;
  }
  return ::mlir::success();
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_TileGPUOps1(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: i64 dense array attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_TileGPUOps1(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_TileGPUOps1(attr, attrName, [op]() {
    return op->emitOpError();
  });
}

static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_TileGPUOps2(
    ::mlir::Attribute attr, ::llvm::StringRef attrName, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  if (attr && !((::llvm::isa<::mlir::StringAttr>(attr))))
    return emitError() << "attribute '" << attrName
        << "' failed to satisfy constraint: string attribute";
  return ::mlir::success();
}
static ::llvm::LogicalResult __mlir_ods_local_attr_constraint_TileGPUOps2(
    ::mlir::Operation *op, ::mlir::Attribute attr, ::llvm::StringRef attrName) {
  return __mlir_ods_local_attr_constraint_TileGPUOps2(attr, attrName, [op]() {
    return op->emitOpError();
  });
}
namespace mlir::tilegpu {


//===----------------------------------------------------------------------===//
// ::mlir::tilegpu::AddOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

AddOpGenericAdaptorBase::AddOpGenericAdaptorBase(AddOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}


} // namespace detail
AddOpAdaptor::AddOpAdaptor(AddOp op) : AddOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult AddOpAdaptor::verify(::mlir::Location loc) {
  return ::mlir::success();
}

::llvm::LogicalResult AddOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
      return ::mlir::success();
}

::mlir::Attribute AddOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code AddOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine();
}

std::optional<mlir::Attribute> AddOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
  return std::nullopt;
}

void AddOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
}

void AddOp::walkInherentAttrs(::mlir::MLIRContext *ctx, Properties &prop, ::llvm::function_ref<void(::llvm::StringRef, ::mlir::Attribute &)> visitor) {
}

::llvm::LogicalResult AddOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    return ::mlir::success();
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Type sum, ::mlir::Value lhs, ::mlir::Value rhs) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addTypes(sum);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Type sum, ::mlir::Value lhs, ::mlir::Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(sum)>(sum), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<AddOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<AddOp>(__res__);
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Type sum, ::mlir::Value lhs, ::mlir::Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(sum)>(sum), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

void AddOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  assert(resultTypes.size() == 1u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<AddOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<AddOp>(__res__);
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs));
}

void AddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<AddOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<AddOp>(__res__);
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void AddOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 1u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

AddOp AddOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<AddOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<AddOp>(__res__);
}

AddOp AddOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult AddOp::verifyInvariantsImpl() {
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps1(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSResults(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps1(*this, v.getType(), "result", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult AddOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult AddOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}


} // namespace mlir::tilegpu
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::AddOp)

namespace mlir::tilegpu {


//===----------------------------------------------------------------------===//
// ::mlir::tilegpu::GemmOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

GemmOpGenericAdaptorBase::GemmOpGenericAdaptorBase(GemmOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::ArrayRef<int64_t> GemmOpGenericAdaptorBase::getTile() {
  auto attr = getTileAttr();
  return attr;
}

::llvm::StringRef GemmOpGenericAdaptorBase::getEpilogues() {
  auto attr = getEpiloguesAttr();
  return attr.getValue();
}


} // namespace detail
GemmOpAdaptor::GemmOpAdaptor(GemmOp op) : GemmOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult GemmOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_epilogues = getProperties().epilogues; (void)tblgen_epilogues;
  if (!tblgen_epilogues) return emitError(loc, "'tilegpu.gemm' op requires attribute 'epilogues'");
  auto tblgen_tile = getProperties().tile; (void)tblgen_tile;
  if (!tblgen_tile) return emitError(loc, "'tilegpu.gemm' op requires attribute 'tile'");

  if (tblgen_tile && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_tile))))
    return emitError(loc, "'tilegpu.gemm' op attribute 'tile' failed to satisfy constraint: i64 dense array attribute");

  if (tblgen_epilogues && !((::llvm::isa<::mlir::StringAttr>(tblgen_epilogues))))
    return emitError(loc, "'tilegpu.gemm' op attribute 'epilogues' failed to satisfy constraint: string attribute");
  return ::mlir::success();
}

::llvm::LogicalResult GemmOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.epilogues;
       auto attr = dict.get("epilogues");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `epilogues` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  {
    auto &propStorage = prop.tile;
       auto attr = dict.get("tile");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tile` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute GemmOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.epilogues;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("epilogues",
                                       propStorage));
    }

    {
      const auto &propStorage = prop.tile;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("tile",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code GemmOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.epilogues.getAsOpaquePointer()), 
    llvm::hash_value(prop.tile.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> GemmOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "epilogues")
      return prop.epilogues;

    if (name == "tile")
      return prop.tile;
  return std::nullopt;
}

void GemmOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "epilogues") {
       prop.epilogues = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.epilogues)>>(value);
       return;
    }

    if (name == "tile") {
       prop.tile = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.tile)>>(value);
       return;
    }
}

void GemmOp::walkInherentAttrs(::mlir::MLIRContext *ctx, Properties &prop, ::llvm::function_ref<void(::llvm::StringRef, ::mlir::Attribute &)> visitor) {
    if (prop.epilogues) {
      ::mlir::Attribute value = prop.epilogues;
      ::mlir::Attribute originalValue = value;
      visitor("epilogues", value);
      if (value != originalValue)
        setInherentAttr(prop, "epilogues", value);
    }

    if (prop.tile) {
      ::mlir::Attribute value = prop.tile;
      ::mlir::Attribute originalValue = value;
      visitor("tile", value);
      if (value != originalValue)
        setInherentAttr(prop, "tile", value);
    }
}

::llvm::LogicalResult GemmOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getEpiloguesAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps2(attr, "epilogues", emitError)))
        return ::mlir::failure();
    }

    {
      ::mlir::Attribute attr = attrs.get(getTileAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps1(attr, "tile", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult GemmOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.epilogues)))
    return ::mlir::failure();

  if (::mlir::failed(reader.readAttribute(prop.tile)))
    return ::mlir::failure();
  return ::mlir::success();
}

void GemmOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.epilogues);
  writer.writeAttribute(prop.tile);
}

::llvm::ArrayRef<int64_t> GemmOp::getTile() {
  auto attr = getTileAttr();
  return attr;
}

::llvm::StringRef GemmOp::getEpilogues() {
  auto attr = getEpiloguesAttr();
  return attr.getValue();
}

void GemmOp::setTile(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().tile = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void GemmOp::setEpilogues(::llvm::StringRef attrValue) {
  getProperties().epilogues = ::mlir::Builder((*this)->getContext()).getStringAttr(attrValue);
}

void GemmOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = tile;
  odsState.getOrAddProperties<Properties>().epilogues = epilogues;
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
}

void GemmOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = tile;
  odsState.getOrAddProperties<Properties>().epilogues = epilogues;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile, ::mlir::StringAttr epilogues) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
}

void GemmOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = odsBuilder.getDenseI64ArrayAttr(tile);
  odsState.getOrAddProperties<Properties>().epilogues = odsBuilder.getStringAttr(epilogues);
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  return create(builder, builder.getLoc(), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
}

void GemmOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  odsState.addOperands(lhs);
  odsState.addOperands(rhs);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = odsBuilder.getDenseI64ArrayAttr(tile);
  odsState.getOrAddProperties<Properties>().epilogues = odsBuilder.getStringAttr(epilogues);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value lhs, ::mlir::Value rhs, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile, ::llvm::StringRef epilogues) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(lhs)>(lhs), std::forward<decltype(rhs)>(rhs), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile), std::forward<decltype(epilogues)>(epilogues));
}

void GemmOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<GemmOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void GemmOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 3u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

GemmOp GemmOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<GemmOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<GemmOp>(__res__);
}

GemmOp GemmOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult GemmOp::verifyInvariantsImpl() {
  auto tblgen_epilogues = getProperties().epilogues; (void)tblgen_epilogues;
  if (!tblgen_epilogues) return emitOpError("requires attribute 'epilogues'");
  auto tblgen_tile = getProperties().tile; (void)tblgen_tile;
  if (!tblgen_tile) return emitOpError("requires attribute 'tile'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps1(*this, tblgen_tile, "tile")))
    return ::mlir::failure();

  if (::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps2(*this, tblgen_epilogues, "epilogues")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup2 = getODSOperands(2);

    for (auto v : valueGroup2) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult GemmOp::verifyInvariants() {
  if(::mlir::succeeded(verifyInvariantsImpl()) && ::mlir::succeeded(verify()))
    return ::mlir::success();
  return ::mlir::failure();
}

::llvm::LogicalResult GemmOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.tile;
    auto tileAttrName = ::mlir::StringAttr::get(ctx, "tile");
    auto attr = dict.get(tileAttrName);
    usedKeys.insert(tileAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for tile in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tile` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  {

    auto &propStorage = prop.epilogues;
    auto epiloguesAttrName = ::mlir::StringAttr::get(ctx, "epilogues");
    auto attr = dict.get(epiloguesAttrName);
    usedKeys.insert(epiloguesAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for epilogues in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `epilogues` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void GemmOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  {
    auto valueRange = getODSOperandIndexAndLength(0);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Read::get(), &getOperation()->getOpOperand(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
  {
    auto valueRange = getODSOperandIndexAndLength(1);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Read::get(), &getOperation()->getOpOperand(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
  {
    auto valueRange = getODSOperandIndexAndLength(2);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Write::get(), &getOperation()->getOpOperand(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
}


} // namespace mlir::tilegpu
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::GemmOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::detail::GemmOpGenericAdaptorBase::Properties)

namespace mlir::tilegpu {


//===----------------------------------------------------------------------===//
// ::mlir::tilegpu::ReluOp definitions
//===----------------------------------------------------------------------===//

namespace detail {

ReluOpGenericAdaptorBase::ReluOpGenericAdaptorBase(ReluOp op) : odsAttrs(op->getRawDictionaryAttrs()), odsOpName(op->getName()), properties(op.getProperties()), odsRegions(op->getRegions()) {}

::llvm::ArrayRef<int64_t> ReluOpGenericAdaptorBase::getTile() {
  auto attr = getTileAttr();
  return attr;
}


} // namespace detail
ReluOpAdaptor::ReluOpAdaptor(ReluOp op) : ReluOpGenericAdaptor(op->getOperands(), op) {}

::llvm::LogicalResult ReluOpAdaptor::verify(::mlir::Location loc) {
  auto tblgen_tile = getProperties().tile; (void)tblgen_tile;
  if (!tblgen_tile) return emitError(loc, "'tilegpu.relu' op requires attribute 'tile'");

  if (tblgen_tile && !((::llvm::isa<::mlir::DenseI64ArrayAttr>(tblgen_tile))))
    return emitError(loc, "'tilegpu.relu' op attribute 'tile' failed to satisfy constraint: i64 dense array attribute");
  return ::mlir::success();
}

::llvm::LogicalResult ReluOp::setPropertiesFromAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }

  {
    auto &propStorage = prop.tile;
       auto attr = dict.get("tile");
    if (attr) {
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tile` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }
  return ::mlir::success();
}

::mlir::Attribute ReluOp::getPropertiesAsAttr(::mlir::MLIRContext *ctx, const Properties &prop) {
    ::mlir::SmallVector<::mlir::NamedAttribute> attrs;
    ::mlir::Builder odsBuilder{ctx};

    {
      const auto &propStorage = prop.tile;
      if (propStorage)
        attrs.push_back(odsBuilder.getNamedAttr("tile",
                                       propStorage));
    }

  if (!attrs.empty())
    return odsBuilder.getDictionaryAttr(attrs);
  return {};
}

llvm::hash_code ReluOp::computePropertiesHash(const Properties &prop) {
  using llvm::hash_value;
  return llvm::hash_combine(
    llvm::hash_value(prop.tile.getAsOpaquePointer()));
}

std::optional<mlir::Attribute> ReluOp::getInherentAttr(::mlir::MLIRContext *ctx, const Properties &prop, llvm::StringRef name) {
    if (name == "tile")
      return prop.tile;
  return std::nullopt;
}

void ReluOp::setInherentAttr(Properties &prop, llvm::StringRef name, mlir::Attribute value) {
    if (name == "tile") {
       prop.tile = ::llvm::dyn_cast_or_null<std::remove_reference_t<decltype(prop.tile)>>(value);
       return;
    }
}

void ReluOp::walkInherentAttrs(::mlir::MLIRContext *ctx, Properties &prop, ::llvm::function_ref<void(::llvm::StringRef, ::mlir::Attribute &)> visitor) {
    if (prop.tile) {
      ::mlir::Attribute value = prop.tile;
      ::mlir::Attribute originalValue = value;
      visitor("tile", value);
      if (value != originalValue)
        setInherentAttr(prop, "tile", value);
    }
}

::llvm::LogicalResult ReluOp::verifyInherentAttrs(::mlir::OperationName opName, ::mlir::NamedAttrList &attrs, llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
    {
      ::mlir::Attribute attr = attrs.get(getTileAttrName(opName));
      if (attr && ::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps1(attr, "tile", emitError)))
        return ::mlir::failure();
    }
    return ::mlir::success();
}

::llvm::LogicalResult ReluOp::readProperties(::mlir::DialectBytecodeReader &reader, ::mlir::OperationState &state) {
  auto &prop = state.getOrAddProperties<Properties>(); (void)prop;
  if (::mlir::failed(reader.readAttribute(prop.tile)))
    return ::mlir::failure();
  return ::mlir::success();
}

void ReluOp::writeProperties(::mlir::DialectBytecodeWriter &writer) {
  auto &prop = getProperties(); (void)prop;
  writer.writeAttribute(prop.tile);
}

::llvm::ArrayRef<int64_t> ReluOp::getTile() {
  auto attr = getTileAttr();
  return attr;
}

void ReluOp::setTile(::llvm::ArrayRef<int64_t> attrValue) {
  getProperties().tile = ::mlir::Builder((*this)->getContext()).getDenseI64ArrayAttr(attrValue);
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  odsState.addOperands(input);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = tile;
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  odsState.addOperands(input);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = tile;
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::mlir::DenseI64ArrayAttr tile) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  odsState.addOperands(input);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = odsBuilder.getDenseI64ArrayAttr(tile);
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  return create(builder, builder.getLoc(), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
}

void ReluOp::build(::mlir::OpBuilder &odsBuilder, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  odsState.addOperands(input);
  odsState.addOperands(output);
  odsState.getOrAddProperties<Properties>().tile = odsBuilder.getDenseI64ArrayAttr(tile);
  assert(resultTypes.size() == 0u && "mismatched number of results");
  odsState.addTypes(resultTypes);
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::Value input, ::mlir::Value output, ::llvm::ArrayRef<int64_t> tile) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(input)>(input), std::forward<decltype(output)>(output), std::forward<decltype(tile)>(tile));
}

void ReluOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.addAttributes(attributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);

  if (!attributes.empty()) {
    (void)odsState.getOrAddProperties<ReluOp::Properties>();
    ::mlir::PropertyRef properties = odsState.getRawProperties();
    std::optional<::mlir::RegisteredOperationName> info =
      odsState.name.getRegisteredInfo();
    if (failed(info->setOpPropertiesFromAttribute(odsState.name, properties,
        odsState.attributes.getDictionary(odsState.getContext()), nullptr)))
      ::llvm::report_fatal_error("Property conversion failed.");
  }
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, ::llvm::ArrayRef<::mlir::NamedAttribute> attributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(attributes)>(attributes));
}

void ReluOp::build(::mlir::OpBuilder &, ::mlir::OperationState &odsState, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  assert(operands.size() == 2u && "mismatched number of parameters");
  odsState.addOperands(operands);
  odsState.useProperties(const_cast<Properties&>(properties));
  odsState.addAttributes(discardableAttributes);
  assert(resultTypes.size() == 0u && "mismatched number of return types");
  odsState.addTypes(resultTypes);
}

ReluOp ReluOp::create(::mlir::OpBuilder &builder, ::mlir::Location location, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  ::mlir::OperationState __state__(location, getOperationName());
  build(builder, __state__, std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
  auto __res__ = builder.create(__state__);
  assert((::llvm::isa<ReluOp>(__res__)) && "builder didn't return the right type");
  return ::llvm::cast<ReluOp>(__res__);
}

ReluOp ReluOp::create(::mlir::ImplicitLocOpBuilder &builder, ::mlir::TypeRange resultTypes, ::mlir::ValueRange operands, const Properties &properties, ::llvm::ArrayRef<::mlir::NamedAttribute> discardableAttributes) {
  return create(builder, builder.getLoc(), std::forward<decltype(resultTypes)>(resultTypes), std::forward<decltype(operands)>(operands), std::forward<decltype(properties)>(properties), std::forward<decltype(discardableAttributes)>(discardableAttributes));
}

::llvm::LogicalResult ReluOp::verifyInvariantsImpl() {
  auto tblgen_tile = getProperties().tile; (void)tblgen_tile;
  if (!tblgen_tile) return emitOpError("requires attribute 'tile'");

  if (::mlir::failed(__mlir_ods_local_attr_constraint_TileGPUOps1(*this, tblgen_tile, "tile")))
    return ::mlir::failure();
  {
    unsigned index = 0; (void)index;
    auto valueGroup0 = getODSOperands(0);

    for (auto v : valueGroup0) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
    auto valueGroup1 = getODSOperands(1);

    for (auto v : valueGroup1) {
      if (::mlir::failed(__mlir_ods_local_type_constraint_TileGPUOps2(*this, v.getType(), "operand", index++)))
        return ::mlir::failure();
    }
  }
  return ::mlir::success();
}

::llvm::LogicalResult ReluOp::verifyInvariants() {
  return verifyInvariantsImpl();
}

::llvm::LogicalResult ReluOp::setPropertiesFromParsedAttr(Properties &prop, ::mlir::Attribute attr, ::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError) {
  ::mlir::DictionaryAttr dict = ::llvm::dyn_cast<::mlir::DictionaryAttr>(attr);
  if (!dict) {
    emitError() << "expected DictionaryAttr to set properties";
    return ::mlir::failure();
  }
  // keep track of used keys in the input dictionary to be able to error out
  // if there are some unknown ones.
  ::mlir::DenseSet<::mlir::StringAttr> usedKeys;
  ::mlir::MLIRContext *ctx = dict.getContext();
  (void)ctx;
  {

    auto &propStorage = prop.tile;
    auto tileAttrName = ::mlir::StringAttr::get(ctx, "tile");
    auto attr = dict.get(tileAttrName);
    usedKeys.insert(tileAttrName);
    if (attr || /*isRequired=*/true) {
      if (!attr) {
        emitError() << "expected key entry for tile in DictionaryAttr to set "
                   "Properties.";
        return ::mlir::failure();
      }
      auto convertedAttr = ::llvm::dyn_cast<std::remove_reference_t<decltype(propStorage)>>(attr);
      if (convertedAttr) {
        propStorage = convertedAttr;
      } else {
        emitError() << "Invalid attribute `tile` in property conversion: " << attr;
        return ::mlir::failure();
      }
    }
  }

  for (::mlir::NamedAttribute attr : dict) {
    if (!usedKeys.contains(attr.getName()))
      return emitError() << "unknown key '" << attr.getName() <<
          "' when parsing properties dictionary";
  }
  return ::mlir::success();
}

void ReluOp::getEffects(::llvm::SmallVectorImpl<::mlir::SideEffects::EffectInstance<::mlir::MemoryEffects::Effect>> &effects) {
  {
    auto valueRange = getODSOperandIndexAndLength(0);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Read::get(), &getOperation()->getOpOperand(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
  {
    auto valueRange = getODSOperandIndexAndLength(1);
    for (unsigned idx = valueRange.first; idx < valueRange.first + valueRange.second; idx++) {
      effects.emplace_back(::mlir::MemoryEffects::Write::get(), &getOperation()->getOpOperand(idx), 0, false, ::mlir::SideEffects::DefaultResource::get());
    }
  }
}


} // namespace mlir::tilegpu
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::ReluOp)
MLIR_DEFINE_EXPLICIT_TYPE_ID(::mlir::tilegpu::detail::ReluOpGenericAdaptorBase::Properties)


#endif // GET_OP_CLASSES

