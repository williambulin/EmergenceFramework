add_library(
  framework SHARED

  ${CMAKE_CURRENT_LIST_DIR}/Game.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Game.hpp
  ${CMAKE_CURRENT_LIST_DIR}/GameHost.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Libraries/Vulkan.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Log/Color.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Log/Logger.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Log/Logger.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Math.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Platform.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Renderer/Vulkan/Vulkan.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Renderer/Vulkan/Vulkan.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Renderer/Vulkan/QueueFamilies.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Renderer/Vulkan/QueueFamilies.hpp
  ${CMAKE_CURRENT_LIST_DIR}/SharedLibrary.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Thread/GameThread.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Thread/Thread.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Thread/Thread.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Window/GLFW.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Window/GLFW.hpp
  ${CMAKE_CURRENT_LIST_DIR}/Window/Window.hpp
)

target_compile_definitions(
  framework PRIVATE

  SHARED_LIBRARY_EXPORT
)

target_include_directories(
  framework PUBLIC

  ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(
  framework PRIVATE

  ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(
  framework PUBLIC

  glm
)

target_link_libraries(
  framework PRIVATE

  glfw
  ${Vulkan_LIBRARIES}
)
