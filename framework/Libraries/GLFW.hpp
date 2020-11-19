#pragma once

#include "Platform.hpp"

#pragma warning(push)
#pragma warning(disable : 4068)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"

#define GLFW_INCLUDE_VULKAN
// #define GLFW_EXPOSE_NATIVE_WIN32
// #define VK_USE_PLATFORM_WIN32_KHR

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#pragma clang diagnostic pop
#pragma warning(pop)
