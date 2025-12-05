cmake_minimum_required(VERSION 3.16)
project(MyCppProject LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Recommended compiler flags for modern C++ (adjust as needed)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Optionally enable clang-tidy for automatic static analysis
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=cppcoreguidelines-*,modernize-*;--extra-arg-before=--driver-mode=g++")
    else()
        message(WARNING "ENABLE_CLANG_TIDY=ON but clang-tidy was not found on PATH. Skipping clang-tidy setup.")
    endif()
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
add_executable(prf ${SOURCES})