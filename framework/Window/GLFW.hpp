#pragma once

#include "Window.hpp"
#include "SharedLibrary.hpp"
#include "Libraries/GLFW.hpp"

#include <stdexcept>

namespace Window {
  class GLFW;
}

class shared Window::GLFW final : public Window {
private:
  GLFWwindow *m_window{nullptr};

public:
  explicit GLFW();
  GLFW(GLFW const &) = delete;
  ~GLFW() final;

  GLFW &operator=(GLFW const &) = delete;

  [[nodiscard]] bool isOpen() const final;
  void               close() final;

  void processMessages() final;

  [[nodiscard]] auto getRequiredVulkanExtensions() -> std::vector<char const *> final;
  [[nodiscard]] auto createVulkanSurface(vk::Instance &instance) -> vk::SurfaceKHR final;
};
