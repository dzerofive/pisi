# Global settings
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


# Main project set up
project(Pisi VERSION 1.0.1.2)
# TODO: Move vulkan things to separate library
add_executable(Pisi pisi.cpp vk/pisi_window.cpp)
target_link_libraries(Pisi glfw vulkan)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

configure_file(PisiConfig.hpp.in PisiConfig.hpp)
