#include "sln_device.hpp"

#define VULKAN_HPP_NO_CONSTRUCTORS

using namespace sln;

Device::Device() {
    create_glfw_window();
    create_vulkan_instance();
    if (enable_validation_layers) check_validation_layer_support();
    pick_physical_device();
    create_logical_device();
    create_surface();
}
Device::~Device() {
    device.destroy(nullptr);
    instance.destroySurfaceKHR(surface, nullptr);
    instance.destroy(nullptr);
    destroy_glfw_window();
}


// One line functions
void*        Device::get_window()        { return window; }
vk::Device   Device::get_device()        { return device; }
vk::Instance Device::get_instance()      { return instance; }
vk::Queue    Device::get_graphic_queue() { return graphic_queue; }
bool         Device::should_close()      { return window.shouldClose(); }
void         Device::poll_events()       { return vkfw::pollEvents(); }


void Device::create_vulkan_instance() {
    // Get platform specific GLFW exntensions for Vulkan
    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions;
    glfw_extensions = vkfw::getRequiredInstanceExtensions(&glfw_extension_count);

    vk::ApplicationInfo app_info{};
    app_info.sType              = vk::StructureType::eApplicationInfo;
    app_info.pApplicationName   = "Siltstone 3";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "No engine";
    app_info.engineVersion      = 1;
    app_info.apiVersion         = VK_API_VERSION_1_3;
    vk::InstanceCreateInfo inst_info{};
    inst_info.sType                   = vk::StructureType::eInstanceCreateInfo;
    inst_info.pApplicationInfo        = &app_info;
    inst_info.enabledExtensionCount   = glfw_extension_count;
    inst_info.ppEnabledExtensionNames = glfw_extensions;
    inst_info.enabledLayerCount       = 0;

    if (vk::createInstance(&inst_info, nullptr, &instance) != vk::Result::eSuccess)
        throw std::runtime_error("Failed to create Vulkan instance!");
}


void Device::create_glfw_window() {
    vkfw::init();
    window = vkfw::createWindow(window_width, window_height, window_title.data(), {}, nullptr);
}
void Device::destroy_glfw_window() {
    window.destroy();
    vkfw::terminate();
}


void Device::check_validation_layer_support() {
    vk::Result result;

    uint32_t layer_count;
    result = vk::enumerateInstanceLayerProperties(&layer_count, nullptr);
    assert(result == vk::Result::eSuccess && "Failed to enumerate instance layer properties (1).");

    std::vector<vk::LayerProperties> available_layers(layer_count);
    result = vk::enumerateInstanceLayerProperties(&layer_count, available_layers.data());
    assert(result == vk::Result::eSuccess && "Failed to enumerate instance layer properties (2).");

    for (const char* layer_name : validation_layers) {
        bool layer_found = false;

        for (const vk::LayerProperties& layer_properties : available_layers) {
            if (strcmp(layer_name, layer_properties.layerName) == 0) {
                layer_found = true;
                break;
            }
            if (!layer_found)
                throw std::runtime_error("Requested validation layres not found.");
        }
    }
}


void Device::pick_physical_device() {
    vk::Result result;

    uint32_t device_count = 0;
    result = instance.enumeratePhysicalDevices(&device_count, nullptr);
    assert(result == vk::Result::eSuccess && "Failed to enumerate physical devices (1).");

    if (device_count == 0)
        throw std::runtime_error("No Vulkan-capable device found.");

    std::vector<vk::PhysicalDevice> devices(device_count);
    result = instance.enumeratePhysicalDevices(&device_count, devices.data());
    assert(result == vk::Result::eSuccess && "Failed to enumerate physical devices (2).");

    for(const vk::PhysicalDevice& device : devices)
        check_physical_device(device);

    //FIXME: Manual selection of device
    physical_device = devices[0];
}


void Device::check_physical_device(vk::PhysicalDevice device) {
    vk::PhysicalDeviceProperties device_properties = device.getProperties();
    vk::PhysicalDeviceFeatures device_features = device.getFeatures();


    std::cout << "Vulkan-capable device found: " << device_properties.deviceName << '\n';
}


QueueFamilyIndices Device::find_queue_families(vk::PhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    device.getQueueFamilyProperties(&queue_family_count, nullptr);

    std::vector<vk::QueueFamilyProperties> queue_families(queue_family_count);
    device.getQueueFamilyProperties(&queue_family_count, queue_families.data());

    uint32_t i = 0;
    for(const vk::QueueFamilyProperties& queue_family : queue_families) {
        if (queue_family.queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphics_family = i;
            indices.present_family = i;
            break;
        }
        i++;
    }

    return indices;
}


void Device::create_logical_device() {
    QueueFamilyIndices indices = find_queue_families(physical_device);

    vk::DeviceQueueCreateInfo queue_create_info {};
    queue_create_info.sType = vk::StructureType::eDeviceQueueCreateInfo;
    queue_create_info.queueFamilyIndex = indices.graphics_family.value();
    queue_create_info.queueCount = 1;
    float queue_priority = 1.0f;
    queue_create_info.pQueuePriorities = &queue_priority;

    vk::PhysicalDeviceFeatures device_features {};

    vk::DeviceCreateInfo create_info {};
    create_info.sType = vk::StructureType::eDeviceCreateInfo;
    create_info.pQueueCreateInfos = &queue_create_info;
    create_info.queueCreateInfoCount = 1;
    create_info.pEnabledFeatures = &device_features;
    // Deprecated in Vulkan 1.3
    if (enable_validation_layers) {
        create_info.enabledLayerCount = validation_layers.size();
        create_info.ppEnabledLayerNames = validation_layers.data();
    } else {
        create_info.enabledLayerCount = 0;
    }

    if (physical_device.createDevice(&create_info, nullptr, &device) != vk::Result::eSuccess)
        throw std::runtime_error("Failed to create logical device.");
}

void Device::create_surface() {
    surface = vkfw::createWindowSurface(instance, window, nullptr);
}
