#pragma once

// third-party
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

// std
#include <string>

namespace pisi {
class PisiWindow {
public:
    // Window object pointer
    GLFWwindow *window;
    // Window settings
    bool isResizeable;
    uint32_t width;
    uint32_t height;
    const char* title;

    // Create objects and init variables, clean up in destructor
    PisiWindow(uint32_t w, uint32_t h, const char* t, bool isRs = GLFW_FALSE);
    ~PisiWindow();
};
} // namespace pisi
