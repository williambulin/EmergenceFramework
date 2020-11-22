#include "SwapchainInfo.hpp"

Renderer::Vulkan::SwapchainInfo::SwapchainInfo(vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface) {
  surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
  surfaceFormats      = physicalDevice.getSurfaceFormatsKHR(surface);
  presentModes        = physicalDevice.getSurfacePresentModesKHR(surface);
}

bool Renderer::Vulkan::SwapchainInfo::isComplete() const {
  return !surfaceFormats.empty() && !presentModes.empty();
}

auto Renderer::Vulkan::SwapchainInfo::findSurfaceFormat() const -> vk::SurfaceFormatKHR {
  for (auto const &surfaceFormat : surfaceFormats)
    if (surfaceFormat.format == vk::Format::eB8G8R8A8Srgb)
      return surfaceFormat;
  return surfaceFormats.front();
}

auto Renderer::Vulkan::SwapchainInfo::findPresentMode() const -> vk::PresentModeKHR {
  for (auto const &presentMode : presentModes)
    if (presentMode == vk::PresentModeKHR::eMailbox)
      return presentMode;
  return vk::PresentModeKHR::eFifo;
}

auto Renderer::Vulkan::SwapchainInfo::findExtent(glm::vec2 &&windowSize) const -> vk::Extent2D {
  if (surfaceCapabilities.currentExtent.height != UINT32_MAX)
    return surfaceCapabilities.currentExtent;

  windowSize = glm::clamp(windowSize, glm::vec2{surfaceCapabilities.minImageExtent.width, surfaceCapabilities.minImageExtent.height}, glm::vec2{surfaceCapabilities.maxImageExtent.width, surfaceCapabilities.maxImageExtent.height});
  return {static_cast<uint32_t>(windowSize.x), static_cast<uint32_t>(windowSize.y)};
}
