cmake_minimum_required(VERSION 3.10)
project(Siltstone)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED true)

add_executable(Siltstone main.cpp sln_device.cpp)
target_include_directories(Siltstone PRIVATE ../thirdparty)
target_link_libraries(Siltstone glfw vulkan)
