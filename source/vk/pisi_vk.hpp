#pragma once

#include <vulkan/vulkan.hpp>

// std
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/log/trivial.hpp>


namespace vk {
    struct Instance;
}

namespace pisi::vulkan {
    void create_instance();

}
