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
add_dependencies(TileGPU MLIRTileGPUOpsIncGen)