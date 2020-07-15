# CMakeList.txt : CMake project for CBenchmark, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package("Boost")
message(STATUS "Boost path: ${Boost_INCLUDE_DIR}")
include_directories(${Boost_INCLUDE_DIR})
# Add source to this project's executable.
add_executable (CBenchmark "CBenchmark.cpp" "CBenchmark.hpp" "main.cpp")

# TODO: Add tests and install targets if needed.
