cmake_minimum_required(VERSION 3.20)

project(vkr
  VERSION 0.1.0
  LANGUAGES C CXX)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Setting build type to debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)

set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_XCB_KHR)
add_subdirectory(deps/volk)

add_subdirectory(deps/VulkanMemoryAllocator)

set(SPIRV_REFLECT_EXECUTABLE OFF)
set(SPIRV_REFLECT_EXAMPLES OFF)
set(SPIRV_REFLECT_STATIC_LIB ON)
add_subdirectory(deps/SPIRV-Reflect)

file(GLOB_RECURSE GLSL_SOURCE_FILES
  "${CMAKE_SOURCE_DIR}/res/shaders/*.vert"
  "${CMAKE_SOURCE_DIR}/res/shaders/*.frag"
  "${CMAKE_SOURCE_DIR}/res/shaders/*.comp")

set(GLSL_VALIDATOR glslangValidator)

message(STATUS "Building Shaders")
foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${CMAKE_SOURCE_DIR}/res/shaders/${FILE_NAME}.spv")
  #message(STATUS ${GLSL})
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
  shaders
  DEPENDS ${SPIRV_BINARY_FILES}
  )


find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(SHADERC REQUIRED shaderc)

file(GLOB SRCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB INCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(vkr
  ${SRCS} ${INCS})

target_link_libraries(vkr PUBLIC ${GLFW_LIBRARIES} volk VulkanMemoryAllocator ${SHADERC_LIBRARIES} spirv-reflect-static)
target_include_directories(vkr PUBLIC ${GLFW_INCLUDE_DIRECTORIES} ${SHADERC_INCLUDE_DIRECTORIES})
add_dependencies(vkr shaders)
