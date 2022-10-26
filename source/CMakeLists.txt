add_executable(Pisi pisi.cpp vk/pisi_window.cpp vk/pisi_vk_instance.cpp)
target_link_libraries(Pisi glfw vulkan)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

configure_file(PisiConfig.hpp.in PisiConfig.hpp)
