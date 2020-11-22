#pragma once

#include "SharedLibrary.hpp"
#include "Libraries/Vulkan.hpp"
#include "Window/Window.hpp"

#include <iostream>
#include <optional>

namespace Renderer::Vulkan {
  class Vulkan;
}

class shared Renderer::Vulkan::Vulkan final {
private:
  vk::UniqueInstance                                                      m_instance{nullptr};
  vk::UniqueSurfaceKHR                                                    m_surface{nullptr};
  vk::UniqueHandle<vk::DebugUtilsMessengerEXT, vk::DispatchLoaderDynamic> m_debugUtilsMessenger{nullptr};
  vk::UniqueDevice                                                        m_device{nullptr};
  vk::Queue                                                               m_graphicsQueue{};
  vk::Queue                                                               m_presentQueue{};

  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData, void *pUserData);

public:
  explicit Vulkan(Window::Window &window);
  Vulkan(Vulkan const &) = delete;
  ~Vulkan()              = default;

  Vulkan &operator=(Vulkan const &) = delete;
};
