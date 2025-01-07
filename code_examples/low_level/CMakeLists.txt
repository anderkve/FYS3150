# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(boxed_particles)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory to the project
include_directories(include)

# Find all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES}
        include/actor.h
        include/precomp.h
        src/box.cpp
        include/box.h
        include/constants.h)

target_precompile_headers(${PROJECT_NAME} PRIVATE include/precomp.h)
