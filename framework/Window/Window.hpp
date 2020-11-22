#pragma once

#include "Libraries/Vulkan.hpp"
#include "Libraries/glm.hpp"

namespace Window {
  class Window;
}

class Window::Window {
public:
  explicit Window();
  Window(Window const &) = delete;
  virtual ~Window();

  Window &operator=(Window const &) = delete;

  [[nodiscard]] virtual bool isOpen() const = 0;
  virtual void               close()        = 0;

  virtual void processMessages() = 0;

  [[nodiscard]] virtual auto getRequiredVulkanExtensions() -> std::vector<char const *>    = 0;
  [[nodiscard]] virtual auto createVulkanSurface(vk::Instance &instance) -> vk::SurfaceKHR = 0;
  [[nodiscard]] virtual auto size() const -> glm::vec2                                     = 0;
};
