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

#pragma clang diagnostic pop
#pragma warning(pop)
