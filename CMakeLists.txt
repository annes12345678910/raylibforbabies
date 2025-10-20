cmake_minimum_required(VERSION 3.20)
project(rfb LANGUAGES CXX)

# C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Library sources
set(RFB_SOURCES
    src/rfb.cpp
)

# Build the library (static)
add_library(rfb STATIC ${RFB_SOURCES})

# Optional: find and link Raylib
find_package(raylib QUIET)
if(raylib_FOUND)
    target_include_directories(rfb PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_libraries(rfb PRIVATE ${raylib_LIBRARIES})
endif()

# Example executable
add_executable(example examples/test.cpp)
target_link_libraries(example PRIVATE rfb)
