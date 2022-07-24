cmake_minimum_required(VERSION 3.20)

project(vkr
  VERSION 0.1.0
  LANGUAGES C CXX)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Setting build type to debug" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_XCB_KHR)
add_subdirectory(deps/volk)

file(GLOB SRCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB INCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(vkr
  ${SRCS} ${INCS})

target_link_libraries(vkr PUBLIC ${GLFW_LIBRARIES} volk)
target_include_directories(vkr PUBLIC ${GLFW_INCLUDE_DIRECTORIES})
