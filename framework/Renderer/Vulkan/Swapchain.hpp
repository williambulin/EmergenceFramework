#pragma once

#include "Libraries/Vulkan.hpp"
#include "Window/Window.hpp"

namespace Renderer::Vulkan {
  class Swapchain;
}

class Renderer::Vulkan::Swapchain final {
public:
  vk::UniqueSwapchainKHR m_swapchain{nullptr};

public:
  explicit Swapchain(Window::Window &window, vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface, vk::Device &device);
  Swapchain(Swapchain const &) = delete;
  ~Swapchain()                 = default;

  Swapchain &operator=(Swapchain const &) = delete;
};
