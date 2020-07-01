# CMakeList.txt : CMake project for String, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

message(STATUS "CMAKE_SYSTEM_ID=${CMAKE_SYSTEM_ID}")

project ("String")
# Add source to this project's executable.
add_executable (String "String.cpp" "String.hpp" "main.cpp")

# TODO: Add tests and install targets if needed.
