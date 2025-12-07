cmake_minimum_required(VERSION 3.16)
project(MyCppProject LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Recommended compiler flags for modern C++ (adjust as needed)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Include directories
include_directories(include)

# Automatically find all source files
file(GLOB SOURCES
    src/*.cc
    src/*/*.cc
    src/*/*/*.cc
)

# Add the executable target
add_executable(partition ${SOURCES})