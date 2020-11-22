#include "GLFW.hpp"

Window::GLFW::GLFW() {
  if (!glfwInit())
    throw std::runtime_error{"Couldn't initialize glfw"};

  if (!glfwVulkanSupported())
    throw std::runtime_error{"Vulkan isn't supported by glfw"};

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  m_window = glfwCreateWindow(1600, 900, "VulkanBase", nullptr, nullptr);
  if (m_window == nullptr)
    throw std::runtime_error{"Couldn't create GLFWwindow"};
}

Window::GLFW::~GLFW() {
  if (m_window != nullptr)
    glfwDestroyWindow(m_window);

  glfwTerminate();
}

bool Window::GLFW::isOpen() const {
  return glfwWindowShouldClose(m_window);
}

void Window::GLFW::close() {
  throw std::runtime_error{"Not implemented"};
}

void Window::GLFW::processMessages() {
  glfwPollEvents();
}

auto Window::GLFW::getRequiredVulkanExtensions() -> std::vector<char const *> {
  uint32_t     glfwExtensionsCount{0};
  char const **glfwExtensions{nullptr};
  glfwExtensions = glfwGetRequiredInstanceExtensions(std::addressof(glfwExtensionsCount));
  return std::vector<char const *>(glfwExtensions, glfwExtensions + glfwExtensionsCount);
}

auto Window::GLFW::createVulkanSurface(vk::Instance &instance) -> vk::SurfaceKHR {
  VkSurfaceKHR surfaceKHR{nullptr};
  glfwCreateWindowSurface(instance, m_window, nullptr, std::addressof(surfaceKHR));
  return vk::SurfaceKHR{surfaceKHR};
}
