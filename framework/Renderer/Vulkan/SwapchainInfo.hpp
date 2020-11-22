#pragma once

#include "Libraries/Vulkan.hpp"
#include "Libraries/glm.hpp"

namespace Renderer::Vulkan {
  class SwapchainInfo;
}

class Renderer::Vulkan::SwapchainInfo final {
public:
  vk::SurfaceCapabilitiesKHR        surfaceCapabilities{};
  std::vector<vk::SurfaceFormatKHR> surfaceFormats{};
  std::vector<vk::PresentModeKHR>   presentModes{};

public:
  explicit SwapchainInfo(vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface);
  SwapchainInfo(SwapchainInfo const &) = delete;
  ~SwapchainInfo()                     = default;

  SwapchainInfo &operator=(SwapchainInfo const &) = delete;

  [[nodiscard]] bool isComplete() const;
  [[nodiscard]] auto findSurfaceFormat() const -> vk::SurfaceFormatKHR;
  [[nodiscard]] auto findPresentMode() const -> vk::PresentModeKHR;
  [[nodiscard]] auto findExtent(glm::vec2 &&windowSize) const -> vk::Extent2D;
};
