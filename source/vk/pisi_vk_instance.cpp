#include "pisi_vk.hpp"

void create_instance() {
    BOOST_LOG_TRIVIAL(trace) << "Creating Vulkan instance";
    // FIXME: Convert vector<string> to const char* const*

    const char* extensions[2] = { "VK_KHR_surface", "VK_KHR_win32_surface" };
    const char* enabled_layers[1] = { "VK_LAYER_KHRONOS_validation" };
    // app_info = application_info
    vk::ApplicationInfo app_info = {};
    app_info.sType = vk::StructureType::eApplicationInfo;
    app_info.apiVersion = VK_API_VERSION_1_3;
    // c_info = create_info
    vk::InstanceCreateInfo c_info = {};
    c_info.sType = vk::StructureType::eInstanceCreateInfo;
    c_info.pApplicationInfo = &app_info;
    c_info.enabledExtensionCount = 2; // FIXME: Here and next 3 lines too ^
    c_info.ppEnabledExtensionNames = extensions;
    c_info.enabledLayerCount = 1;
    c_info.ppEnabledExtensionNames = enabled_layers;

    vk::Instance instance;
    if(vk::createInstance(&c_info, nullptr, &instance) != vk::Result::eSuccess) {
        throw std::runtime_error("Vulkan :: Create Instance :: Failed to create instance!");
    }
};
