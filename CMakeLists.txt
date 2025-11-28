# Build normally: cmake -B build && cmake --build build
# Build with strict checks: cmake -B build -DENABLE_TIDY=ON && cmake --build build

cmake_minimum_required(VERSION 3.16)
project(MyCppProject LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option to enable strict checks (clang-tidy and -Werror)
option(ENABLE_TIDY "Enable clang-tidy and -Werror for strict code quality checks" OFF)

# Recommended compiler flags for modern C++ (adjust as needed)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if(ENABLE_TIDY)
        add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endif()

# Optionally, set clang-tidy for automatic static analysis
if(ENABLE_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=cppcoreguidelines-*,modernize-*")
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