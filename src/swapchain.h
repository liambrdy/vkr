#ifndef SWAPCHAIN_H_
#define SWAPCHAIN_H_

#include <volk.h>

#include <vector>

#include <GLFW/glfw3.h>

struct Swapchain {
    VkSwapchainKHR swapchain;

    VkExtent2D extent;
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    uint32_t imageCount;

    bool vsync;

    std::vector<VkImageView> imageViews;
    std::vector<VkImage> images;
};

void SwapchainCreate(Swapchain *swapchain, GLFWwindow *window, bool vsync);
void SwapchainDestroy(Swapchain *swapchain);

#endif // SWAPCHAIN_H_
