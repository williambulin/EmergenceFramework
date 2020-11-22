#pragma once

#include "Libraries/Vulkan.hpp"
#include "Window/Window.hpp"

namespace Renderer::Vulkan {
  class Swapchain;
}

class Renderer::Vulkan::Swapchain final {
public:
  vk::SurfaceFormatKHR   m_surfaceFormat{};
  vk::PresentModeKHR     m_presentMode{};
  vk::Extent2D           m_extent{};
  vk::UniqueSwapchainKHR m_swapchain{nullptr};
  std::vector<vk::Image> m_images{};

public:
  explicit Swapchain(Window::Window &window, vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface, vk::Device &device);
  Swapchain(Swapchain const &) = delete;
  ~Swapchain()                 = default;

  Swapchain &operator=(Swapchain const &) = delete;
};
