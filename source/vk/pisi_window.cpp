#include "pisi_window.hpp"

namespace pisi {
// Create GLFW window with hints, initialize
// arguments into class member variables
PisiWindow::PisiWindow(uint32_t w, uint32_t h, const char *t, bool isRs)
    : width(w), height(h), title(t), isResizeable(isRs)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, isResizeable);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
}

// Destroy objects and terminate
PisiWindow::~PisiWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
} // namespace pisi
