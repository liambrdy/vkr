#include <cstdio>
#include <cassert>
#include <vector>
#include <cstring>

#include <volk.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "vk_util.h"
#include "context.h"
#include "pipeline.h"

int main(int argc, char *argv[]) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "vkr", nullptr, nullptr);
    assert(window != nullptr);

    volkInitialize();

    InitializeVulkanContext(window);
    InitializePipelineManager();

    PipelineInfo pipelineInfo;
    pipelineInfo.vertPath = "res/shaders/test.vert.spv";
    pipelineInfo.fragPath = "res/shaders/test.frag.spv";
    pipelineInfo.polygonMode = VK_POLYGON_MODE_LINE;
    pipelineInfo.lineWidth = 2.0f;
    VkPipeline pipeline = GetPipeline(pipelineInfo);

    pipelineInfo.lineWidth = 10.0f;
    VkPipeline thickPipeline = GetPipeline(pipelineInfo);

    pipelineInfo.lineWidth = 2.0f;
    VkPipeline samePipeline = GetPipeline(pipelineInfo);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        BeginFrame();

        auto &f = GetFrame();

        VkViewport viewport;
        viewport.x = 0;
        viewport.y = 0;
        viewport.width = 1280;
        viewport.height = 720;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor;
        scissor.extent = { 1280, 720 };
        scissor.offset = { 0, 0 };

        vkCmdBindPipeline(f.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, thickPipeline);
        vkCmdSetViewport(f.commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(f.commandBuffer, 0, 1, &scissor);
        vkCmdDraw(f.commandBuffer, 3, 1, 0, 0);

        EndFrame();
    }

    DestroyPipelineManager();
    ShutdownVulkanContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
