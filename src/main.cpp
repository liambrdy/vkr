#include <cstdio>
#include <cassert>
#include <vector>
#include <cstring>

#include <volk.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "vk_util.h"
#include "context.h"

int main(int argc, char *argv[]) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "vkr", nullptr, nullptr);
    assert(window != nullptr);

    volkInitialize();

    InitializeVulkanContext(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        BeginFrame();

        EndFrame();
    }

    ShutdownVulkanContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
