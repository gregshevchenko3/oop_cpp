# CMakeList.txt : CMake project for Matrix, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package("Boost")
message(STATUS "Boost path: ${Boost_INCLUDE_DIR}")
include_directories(${Boost_INCLUDE_DIR})


# Add source to this project's executable.
add_executable (Matrix "Matrix.cpp" "Matrix.h" "main.cpp" "Matrix.impl.h" 
"../../CBenchmark/CBenchmark/CBenchmark.hpp" "../../CBenchmark/CBenchmark/CBenchmark.cpp"
)
# add_compile_definitions(BENCHMARK_STREAM="std::ofstream(E:/trace.json, std::ofstream::in | std::ofstream::out | std::ofstream::trunc)")

# TODO: Add tests and install targets if needed.
