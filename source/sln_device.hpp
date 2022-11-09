#pragma once

#include <vulkan/vulkan.hpp>
#include <vkfw/vkfw.hpp>

// std
#include <cstring>
#include <cassert>
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <optional>

namespace sln {

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
        std::optional<uint32_t> present_family;
    };

    class Device {
    public:
        Device();
        ~Device();

        Device(const Device& ) = delete;
        Device& operator=( const Device& ) = delete;

        bool should_close();
        void poll_events();
        void* get_window();
        vk::Device   get_device();
        vk::Instance get_instance();
        vk::Queue    get_graphic_queue();


    private:
        // Functions
        void create_glfw_window();
        void create_vulkan_instance();
        void check_validation_layer_support();
        void pick_physical_device();
        void check_physical_device(vk::PhysicalDevice);
        QueueFamilyIndices find_queue_families(vk::PhysicalDevice);
        void create_logical_device();
        void create_surface();

        void destroy_glfw_window();

        // Variables
        const std::vector<const char*> validation_layers = { "VK_LAYER_KHRONOS_validation" };
        #ifdef NDEBUG
                const bool enable_validation_layers = false;
        #else
                const bool enable_validation_layers = true;
        #endif

        const uint32_t window_width = 1280;
        const uint32_t window_height = 720;
        const std::string window_title = "Loliconic 3";
        vkfw::Window window;

        vk::Instance       instance;
        vk::Device         device;
        vk::PhysicalDevice physical_device;
        vk::Queue          graphic_queue;
        vk::SurfaceKHR     surface;
    };

}
