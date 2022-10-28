#include "pisi_vk_device.hpp"

namespace pisi::gfx {


Device::Device() {
    BOOST_LOG_TRIVIAL(trace) << "Creating Pisi Device...";
    list_available_layers();
    create_instance();
}
Device::~Device() {

}


void Device::list_available_layers() {
    vk::Result result;

    uint32_t layer_count;
    result = vk::enumerateInstanceLayerProperties(&layer_count, nullptr);
    assert(result == vk::Result::eSuccess);

    std::vector<vk::LayerProperties> available_layers(layer_count);
    result = vk::enumerateInstanceLayerProperties(&layer_count, available_layers.data());
    assert(result == vk::Result::eSuccess);

    BOOST_LOG_TRIVIAL(trace) << "Available Vulkan layers:";
    for(const auto i: available_layers) {
        BOOST_LOG_TRIVIAL(trace) << '\t' << i.layerName;
    }
}


void Device::create_instance() {
    BOOST_LOG_TRIVIAL(trace) << "Creating Vulkan instance";

    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;

    const std::vector<const char*> extensions = {};
    const std::vector<const char*> enabled_layers = {};

    vk::ApplicationInfo app_info = {}; // app_info = application_info
    app_info.sType = vk::StructureType::eApplicationInfo;
    app_info.pNext = nullptr;
    app_info.pApplicationName = APP_NAME;
    app_info.applicationVersion = VK_MAKE_VERSION(Pisi_VERSION_MAJOR, Pisi_VERSION_MINOR, Pisi_VERSION_PATCH);
    app_info.pEngineName = "No engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_3;
    vk::InstanceCreateInfo c_info = {}; // c_info = create_info
    c_info.sType = vk::StructureType::eInstanceCreateInfo;
    c_info.pNext = nullptr;
    c_info.flags = {};
    c_info.pApplicationInfo = &app_info;
    c_info.enabledExtensionCount = extensions.size();
    c_info.ppEnabledExtensionNames = extensions.data();
    c_info.enabledLayerCount = enabled_layers.size();
    c_info.ppEnabledExtensionNames = enabled_layers.data();

    if(vk::createInstance(&c_info, nullptr, &instance) != vk::Result::eSuccess) {
        throw std::runtime_error("Create Instance :: Failed to create Vulkan instance!");
    }
    BOOST_LOG_TRIVIAL(trace) << "Created Vulkan intance successfully";
};


} // pisi::gfx
