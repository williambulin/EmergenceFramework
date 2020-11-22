#pragma once

#include "Platform.hpp"

#ifdef OS_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#endif

#pragma warning(push)
#pragma warning(disable : 4068)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#include <vulkan/vulkan.hpp>

#define VK_MAKE_VERSION(major, minor, patch) (((static_cast<uint32_t>(major)) << 22) | ((static_cast<uint32_t>(minor)) << 12) | (static_cast<uint32_t>(patch)))
#define VK_API_VERSION_1_0                   VK_MAKE_VERSION(1, 0, 0)  // Patch version should always be set to 0

#pragma clang diagnostic pop
#pragma warning(pop)
