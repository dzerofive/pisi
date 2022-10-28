#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

// std
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/log/trivial.hpp>

#include "../PisiConfig.hpp"

namespace pisi::gfx {
    class Device {
        public:
            Device();
            ~Device();

        private:
            void list_available_layers();
            vk::Instance instance;
            void create_instance();

    };
}
