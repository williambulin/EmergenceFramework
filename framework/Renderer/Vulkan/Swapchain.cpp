#include "Swapchain.hpp"
#include "Renderer/Vulkan/SwapchainInfo.hpp"
#include "Renderer/Vulkan/QueueFamilies.hpp"

#include <iostream>

Renderer::Vulkan::Swapchain::Swapchain(Window::Window &window, vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface, vk::Device &device) {
  SwapchainInfo swapchainInfo{physicalDevice, surface};
  m_surfaceFormat = swapchainInfo.findSurfaceFormat();
  m_presentMode   = swapchainInfo.findPresentMode();
  m_extent        = swapchainInfo.findExtent(window.size());

  QueueFamilies         queueFamilies{physicalDevice, surface};
  std::vector<uint32_t> queueFamiliesIndices{
  queueFamilies.graphicsFamily.value(),
  queueFamilies.presentFamily.value(),
  };
  bool exclusiveMode{std::all_of(queueFamiliesIndices.begin(), queueFamiliesIndices.end(), [&](auto const &queueFamilyIndex) {
    return queueFamilyIndex == queueFamiliesIndices.front();
  })};

  uint32_t                   imageCount{std::clamp(swapchainInfo.surfaceCapabilities.minImageCount + 1, swapchainInfo.surfaceCapabilities.minImageCount, swapchainInfo.surfaceCapabilities.maxImageCount)};
  vk::SwapchainCreateInfoKHR swapchainCreateInfo{
  {},
  surface,
  imageCount,
  m_surfaceFormat.format,
  m_surfaceFormat.colorSpace,
  m_extent,
  1,
  vk::ImageUsageFlagBits::eColorAttachment,  // TODO: Change to dst for postprocessing
  exclusiveMode ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent,
  exclusiveMode ? 0 : static_cast<uint32_t>(queueFamiliesIndices.size()),
  exclusiveMode ? nullptr : queueFamiliesIndices.data(),
  swapchainInfo.surfaceCapabilities.currentTransform,
  vk::CompositeAlphaFlagBitsKHR::eOpaque,  // TODO: For overlays?
  m_presentMode,
  true,
  };

  m_swapchain = device.createSwapchainKHRUnique(swapchainCreateInfo);
  m_images    = device.getSwapchainImagesKHR(m_swapchain.get());
  std::cout << "Got " << m_images.size() << " images out of the swapchain" << '\n';
}
