#include "QueueFamilies.hpp"

Renderer::Vulkan::QueueFamilies::QueueFamilies(vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface) {
  uint32_t i{0};
  auto     queueFamilyProperties{physicalDevice.getQueueFamilyProperties()};
  for (auto const &queueFamilyProperty : queueFamilyProperties) {
    if (queueFamilyProperty.queueFlags & vk::QueueFlagBits::eGraphics)
      graphicsFamily = i;
    if (physicalDevice.getSurfaceSupportKHR(i, surface))
      presentFamily = i;
    ++i;
  }
}

bool Renderer::Vulkan::QueueFamilies::isComplete() const {
  return graphicsFamily.has_value() && presentFamily.has_value();
}
