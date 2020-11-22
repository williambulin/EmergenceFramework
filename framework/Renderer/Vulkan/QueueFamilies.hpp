#pragma once

#include "Libraries/Vulkan.hpp"

#include <optional>

namespace Renderer::Vulkan {
  class QueueFamilies;
}

class Renderer::Vulkan::QueueFamilies final {
public:
  std::optional<uint32_t> graphicsFamily{std::nullopt};
  std::optional<uint32_t> presentFamily{std::nullopt};

public:
  explicit QueueFamilies(vk::PhysicalDevice &physicalDevice, vk::SurfaceKHR &surface);
  QueueFamilies(QueueFamilies const &) = delete;
  ~QueueFamilies()                     = default;

  QueueFamilies &operator=(QueueFamilies const &) = delete;

  [[nodiscard]] bool isComplete() const;
};
