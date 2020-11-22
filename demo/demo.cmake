add_executable(
  demo

  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_compile_definitions(
  demo PRIVATE

  SHARED_LIBRARY_IMPORT
)

get_target_property(FRAMEWORK_INCLUDES framework INCLUDE_DIRECTORIES)

target_include_directories(
  demo PRIVATE

  ${FRAMEWORK_INCLUDES}
)

target_link_libraries(
  demo

  framework
  ${Vulkan_LIBRARIES} # TODO: Remove when renderer fully wrapped
)
