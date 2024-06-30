cmake_minimum_required(VERSION 3.25)
project(CppDataStructures)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "include/*.hpp")

# Add the executable
add_executable(CppDataStructures ${SOURCES})
