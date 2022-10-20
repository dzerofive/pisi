#include <iostream>

// Поки CMake не налаштовано, я використовую наступну команду для збірки:
// Until CMake is not set up, I use following command for build:

// g++ -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXi -o build/test ./source/*.cpp ./source/vk/*.cpp
//                                                               ^
//                                         ця папка у .gitignore |
//                                  this folder is in .gitignore |

// Pisi.cpp це файл для експерементів з іншими інструментами, сам не є інструментом
// Pisi.cpp is a file for experiments with other tools, not a tool by itself

#include "vk/pisi_window.hpp"
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

    while(!glfwWindowShouldClose(window.window)) {
        glfwPollEvents();
    }
}
