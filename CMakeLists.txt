cmake_minimum_required(VERSION 3.20)
project(TileGPU LANGUAGES C CXX)

find_package(MLIR REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}" "${LLVM_CMAKE_DIR}")
include(TableGen)
include(AddLLVM)
include(AddMLIR)

include_directories(${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS})
include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_BINARY_DIR}/include")

add_subdirectory(include/tilegpu)
add_library(TileGPU STATIC lib/TileGPU.cpp)
target_sources(TileGPU PRIVATE lib/TileGPUToGPU.cpp)
add_dependencies(TileGPU MLIRTileGPUOpsIncGen)

target_link_libraries(TileGPU PUBLIC MLIRIR MLIRBytecodeOpInterface MLIRSideEffectInterfaces)
add_executable(tilegpu-opt tools/tilegpu-opt.cpp)
target_link_libraries(tilegpu-opt PRIVATE TileGPU MLIRFuncDialect MLIROptLib)

target_sources(TileGPU PRIVATE lib/TileGPUToGPU.cpp)
target_link_libraries(TileGPU PUBLIC MLIRArithDialect MLIRGPUDialect MLIRPass)

llvm_update_compile_flags(TileGPU)
llvm_update_compile_flags(tilegpu-opt)