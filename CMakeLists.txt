# Global settings
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Main project set up
project(Pisi VERSION 1.0.1.2)
# TODO: Move vulkan things to separate library
add_subdirectory(source)