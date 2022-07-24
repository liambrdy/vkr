#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <volk.h>

#include <GLFW/glfw3.h>

#include <array>

#include "swapchain.h"

constexpr uint32_t FrameOverlap = 2;

struct FrameData {
    VkSemaphore presentSemaphore, renderSemaphore;
    VkFence renderFence;

    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
};

struct Context {
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue queue;
    VkSurfaceKHR surface;

    uint32_t imageIndex;
    Swapchain swapchain;
    std::vector<VkFramebuffer> framebuffers;

    VkRenderPass renderPass;

    std::array<FrameData, FrameOverlap> frames;
    uint32_t frameIndex;
    uint32_t frameCount;
};

extern Context context;

void InitializeVulkanContext(GLFWwindow *window);
void ShutdownVulkanContext();

FrameData &GetFrame();

void BeginFrame();
void EndFrame();

#endif // CONTEXT_H_
