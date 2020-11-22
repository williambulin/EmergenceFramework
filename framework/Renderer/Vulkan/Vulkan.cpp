#include "Vulkan.hpp"
#include "QueueFamilies.hpp"

#include <algorithm>
#include <set>

VKAPI_ATTR VkBool32 VKAPI_CALL Renderer::Vulkan::Vulkan::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, VkDebugUtilsMessengerCallbackDataEXT const *pCallbackData, void *pUserData) {
  static_cast<void>(messageSeverity);
  static_cast<void>(messageType);
  static_cast<void>(pUserData);
  std::cerr << pCallbackData->pMessage << '\n';
  return VK_FALSE;
}

Renderer::Vulkan::Vulkan::Vulkan(Window::Window &window) {
  vk::ApplicationInfo applicationInfo{
  "Vulkan",
  VK_MAKE_VERSION(1, 0, 0),
  "Vulkan Backend",
  VK_MAKE_VERSION(1, 0, 0),
  VK_API_VERSION_1_0,
  };

  auto                      extensions{window.getRequiredVulkanExtensions()};
  std::vector<char const *> layers{
  "VK_LAYER_KHRONOS_validation",
  };

  auto instanceLayerProperties{vk::enumerateInstanceLayerProperties()};
  bool supportsValidationLayers{std::all_of(layers.begin(), layers.end(), [&instanceLayerProperties](auto const &validationLayer) {
    return std::any_of(instanceLayerProperties.begin(), instanceLayerProperties.end(), [&validationLayer](auto const &layerProperty) {
      return std::strcmp(validationLayer, layerProperty.layerName) == 0;
    });
  })};

  if (!supportsValidationLayers) {
    std::cerr << "Requested validation layers not supported, continuing without..." << '\n';
    layers.clear();
  } else
    extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

  vk::InstanceCreateInfo instanceCreateInfo{
  vk::InstanceCreateFlags{},
  std::addressof(applicationInfo),
  layers,
  extensions,
  };

  vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{
  {},
  vk::DebugUtilsMessageSeverityFlagBitsEXT::eError | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
  vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
  debugCallback,
  };

  if (supportsValidationLayers)
    instanceCreateInfo.setPNext(std::addressof(debugUtilsMessengerCreateInfo));

  m_instance = vk::createInstanceUnique(instanceCreateInfo);

  m_surface = window.createVulkanSurface(m_instance.get());

  auto instanceExtensionProperties{vk::enumerateInstanceExtensionProperties()};
  for (auto const &extensionProperty : instanceExtensionProperties)
    std::cout << extensionProperty.extensionName << '\n';

  auto dispatchLoaderDynamic{vk::DispatchLoaderDynamic(m_instance.get(), vkGetInstanceProcAddr)};
  m_debugUtilsMessenger = m_instance->createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfo, nullptr, dispatchLoaderDynamic);

  auto physicalDevices{m_instance->enumeratePhysicalDevices()};
  if (physicalDevices.empty())
    throw std::runtime_error{"Couldn't find any GPUs that supports Vulkan"};

  static const std::vector<char const *> deviceExtensions{
  VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };

  auto physicalDeviceSearch{std::find_if(physicalDevices.begin(), physicalDevices.end(), [&](auto &physicalDevice) {
    QueueFamilies queueFamilies{physicalDevice, m_surface};
    if (!queueFamilies.isComplete())
      return false;

    std::set<std::string> deviceExtensionsSet{deviceExtensions.begin(), deviceExtensions.end()};
    for (auto const &extension : physicalDevice.enumerateDeviceExtensionProperties())
      deviceExtensionsSet.erase(extension.extensionName);

    return deviceExtensionsSet.empty();
  })};

  if (physicalDeviceSearch == physicalDevices.end())
    throw std::runtime_error{"Couldn't find any suitable GPUs that supports Vulkan"};

  auto          physicalDevice{*physicalDeviceSearch};
  QueueFamilies queueFamilies{physicalDevice, m_surface};
  if (!queueFamilies.isComplete())
    throw std::runtime_error{"Couldn't find every needed queue families"};

  std::cout << "Graphics queue index: " << queueFamilies.graphicsFamily.value() << '\n';
  std::cout << "Presentation queue index: " << queueFamilies.presentFamily.value() << '\n';

  float                                  queuePriority{1.0f};
  std::vector<vk::DeviceQueueCreateInfo> deviceQueueCreateInfos{};
  std::set<uint32_t>                     uniqueQueueFamilies{queueFamilies.graphicsFamily.value(), queueFamilies.presentFamily.value()};
  for (auto const &uniqueQueueFamily : uniqueQueueFamilies) {
    deviceQueueCreateInfos.emplace_back(vk::DeviceQueueCreateInfo{
    {},
    uniqueQueueFamily,
    1,
    std::addressof(queuePriority),
    });
  }

  vk::PhysicalDeviceFeatures physicalDeviceFeatures{};

  vk::DeviceCreateInfo deviceCreateInfo{
  {},
  deviceQueueCreateInfos,
  {},
  {},
  std::addressof(physicalDeviceFeatures),
  };

  m_device = physicalDevice.createDeviceUnique(deviceCreateInfo);

  m_graphicsQueue = m_device->getQueue(queueFamilies.graphicsFamily.value(), 0);
  m_presentQueue  = m_device->getQueue(queueFamilies.presentFamily.value(), 0);
}

Renderer::Vulkan::Vulkan::~Vulkan() {
  m_instance->destroySurfaceKHR(m_surface);

  auto dispatchLoaderDynamic{vk::DispatchLoaderDynamic(m_instance.get(), vkGetInstanceProcAddr)};
  m_instance->destroyDebugUtilsMessengerEXT(m_debugUtilsMessenger, nullptr, dispatchLoaderDynamic);
}
