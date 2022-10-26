#include <vulkan/vulkan.hpp>

#include <iostream>

#include "vk/pisi_window.hpp"
#include "vk/pisi_vk.hpp"
#include <PisiConfig.hpp>

#define APP_NAME "Pisi Toolset"

int main() {
    // Створює пусте вікно, починає луп до поки не закриєш
    // Creating empty window, runs loop until closed
    std::cout << "Starting " << APP_NAME << " version " <<
        Pisi_VERSION_MAJOR << '.' <<
        Pisi_VERSION_MINOR << '.' <<
        Pisi_VERSION_PATCH << '.' <<
        Pisi_VERSION_TWEAK << '\n';
    pisi::PisiWindow window(1280, 720, APP_NAME);

    pisi::vulkan::create_instance();

    while(window.shouldClose()) {
        glfwPollEvents();
    }
}
