#pragma once

#include "SharedLibrary.hpp"
#include "Libraries/Vulkan.hpp"
#include "Window/Window.hpp"

#include <iostream>
#include <optional>

namespace Renderer::Vulkan {
  class Vulkan;
}

class shared Renderer::Vulkan::Vulkan final {  // TODO: Remove shared when fully wrapped
private:
  vk::UniqueInstance         m_instance{nullptr};
  vk::SurfaceKHR             m_surface{nullptr};
  vk::DebugUtilsMessengerEXT m_debugUtilsMessenger{nullptr};
  vk::UniqueDevice           m_device{nullptr};
  vk::Queue                  m_graphicsQueue{};
  vk::Queue                  m_presentQueue{};

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData, void *pUserData);

public:
  explicit Vulkan(Window::Window &window);
  Vulkan(Vulkan const &) = delete;
  ~Vulkan();

  Vulkan &operator=(Vulkan const &) = delete;
};
