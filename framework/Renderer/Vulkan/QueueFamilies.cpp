#include "QueueFamilies.hpp"

Renderer::Vulkan::QueueFamilies::QueueFamilies(vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface) {
  uint32_t i{0};
  auto     queueFamilyProperties{physicalDevice.getQueueFamilyProperties()};
  for (auto const &queueFamilyProperty : queueFamilyProperties) {
    if (queueFamilyProperty.queueFlags & vk::QueueFlagBits::eGraphics && (!graphicsFamily.has_value() || (presentFamily.has_value() && i == presentFamily.value())))
      graphicsFamily = i;
    if (physicalDevice.getSurfaceSupportKHR(i, surface) && (!presentFamily.has_value() || (graphicsFamily.has_value() && i == graphicsFamily.value())))
      presentFamily = i;
    ++i;
  }
}

bool Renderer::Vulkan::QueueFamilies::isComplete() const {
  return graphicsFamily.has_value() && presentFamily.has_value();
}
