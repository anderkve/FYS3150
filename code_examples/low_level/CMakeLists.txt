# Minimum required version of CMake
cmake_minimum_required(VERSION 3.29)

# Project name
project(boxed_particles)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Armadillo REQUIRED)
# for GUI
find_package(SFML 3 REQUIRED COMPONENTS Graphics System Window)

# Add the include directory to the project
include_directories(include)

set(SOURCES src/actor.cpp
            src/box.cpp
            mwe.cpp)

file(GLOB HEADERS "include/*.h")

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::System SFML::Window ${ARMADILLO_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE include/precomp.h)
