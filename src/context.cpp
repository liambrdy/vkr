#include "context.h"

#include <vector>
#include <cstring>
#include <cassert>

#include "vk_util.h"

Context context;

static std::vector<const char *> GetGLFWInstanceExtensions(GLFWwindow *window) {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    uint32_t availableExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, nullptr);
    std::vector<VkExtensionProperties> extensionProperties(availableExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &availableExtensionCount, extensionProperties.data());

    std::vector<const char *> extensions;
    for (int i = 0; i < glfwExtensionCount; i++) {
        for (int j = 0; j < extensionProperties.size(); j++) {
            if (std::strcmp(glfwExtensions[i], extensionProperties[j].extensionName) == 0) {
                extensions.push_back(glfwExtensions[i]);
                break;
            }
        }
    }

    return extensions;
}

static VKAPI_PTR VkBool32 DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                 VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                                 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                 void* pUserData)
{
    std::printf("Vulkan Message: %s\n", pCallbackData->pMessage);

    return VK_FALSE;
}


void InitializeVulkanContext(GLFWwindow *window) {
    auto extensions = GetGLFWInstanceExtensions(window);
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    std::vector<const char *> instanceLayers = {"VK_LAYER_KHRONOS_validation"};

    VkApplicationInfo appInfo;
    GetApplicationInfo(&appInfo, "vkr");

    VkDebugUtilsMessengerCreateInfoEXT messengerCreateInfo;
    GetDebugMessengerCreateInfo(&messengerCreateInfo, DebugCallback);

    VkInstanceCreateInfo instanceCreateInfo;
    GetInstanceCreateInfo(&instanceCreateInfo, &appInfo);
    instanceCreateInfo.pNext = &messengerCreateInfo;
    instanceCreateInfo.enabledExtensionCount = extensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
    instanceCreateInfo.enabledLayerCount = instanceLayers.size();
    instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();

    VkCheck(vkCreateInstance(&instanceCreateInfo, nullptr, &context.instance));

    volkLoadInstanceOnly(context.instance);

    VkCheck(vkCreateDebugUtilsMessengerEXT(context.instance, &messengerCreateInfo, nullptr, &context.debugMessenger));

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(context.instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    VkCheck(vkEnumeratePhysicalDevices(context.instance, &deviceCount, devices.data()));
    assert(devices.size() > 0);

    context.physicalDevice = devices[0];

    glfwCreateWindowSurface(context.instance, window, nullptr, &context.surface);

    VkDeviceCreateInfo deviceCreateInfo;
    VkDeviceQueueCreateInfo queueCreateInfo;
    VkPhysicalDeviceFeatures features = {};
    features.samplerAnisotropy = VK_TRUE;
    features.wideLines = VK_TRUE;
    std::vector<const char *> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    GetDeviceCreateInfo(&deviceCreateInfo, deviceExtensions, &features);
    GetQueueCreateInfo(&queueCreateInfo);
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;

    VkCheck(vkCreateDevice(context.physicalDevice, &deviceCreateInfo, nullptr, &context.device));

    volkLoadDevice(context.device);

    vkGetDeviceQueue(context.device, 0, 0, &context.queue);

    SwapchainCreate(&context.swapchain, window, true);

    std::vector<VkAttachmentDescription> attachments;
    std::vector<VkSubpassDescription> subpasses;
    std::vector<VkSubpassDependency> dependencies;

    VkAttachmentDescription colorAttachment;
    GetAttachmentDescription(&colorAttachment, context.swapchain.surfaceFormat.format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    attachments.push_back(colorAttachment);

    VkAttachmentReference colorAttachmentReference;
    colorAttachmentReference.attachment = 0;
    colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.flags = 0;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentReference;
    subpasses.push_back(subpass);

    VkRenderPassCreateInfo renderpassInfo;
    GetRenderPassCreateInfo(&renderpassInfo, attachments, subpasses, dependencies);
    VkCheck(vkCreateRenderPass(context.device, &renderpassInfo, nullptr, &context.renderPass));

    context.framebuffers.resize(context.swapchain.imageCount);
    VkFramebufferCreateInfo framebufferInfo;
    GetFramebufferCreateInfo(&framebufferInfo);
    framebufferInfo.attachmentCount = 1;
    for (uint32_t i = 0; i < context.swapchain.imageCount; i++) {
        std::vector<VkImageView> attachments = { context.swapchain.imageViews[i] };
        framebufferInfo.pAttachments = attachments.data();

        VkCheck(vkCreateFramebuffer(context.device, &framebufferInfo, nullptr, &context.framebuffers[i]));
    }

    context.frameCount = 0;
    context.frameIndex = 0;

    for (auto &frame : context.frames) {
        frame.presentSemaphore = CreateSemaphore();
        frame.renderSemaphore = CreateSemaphore();
        frame.renderFence = CreateFence(VK_FENCE_CREATE_SIGNALED_BIT);

        frame.commandPool = CreateCommandPool(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        frame.commandBuffer = CreateCommandBuffer(frame.commandPool);
    }
}

void ShutdownVulkanContext() {
    vkDeviceWaitIdle(context.device);

    for (const auto &f : context.frames) {
        vkDestroyCommandPool(context.device, f.commandPool, nullptr);

        vkDestroyFence(context.device, f.renderFence, nullptr);
        vkDestroySemaphore(context.device, f.renderSemaphore, nullptr);
        vkDestroySemaphore(context.device, f.presentSemaphore, nullptr);
    }

    for (const auto &f : context.framebuffers)
        vkDestroyFramebuffer(context.device, f, nullptr);

    vkDestroyRenderPass(context.device, context.renderPass, nullptr);

    SwapchainDestroy(&context.swapchain);

    vkDestroyDevice(context.device, nullptr);
    vkDestroySurfaceKHR(context.instance, context.surface, nullptr);
    vkDestroyDebugUtilsMessengerEXT(context.instance, context.debugMessenger, nullptr);
    vkDestroyInstance(context.instance, nullptr);
}

FrameData &GetFrame() {
    return context.frames[context.frameIndex];
}

void BeginFrame() {
    auto &f = GetFrame();

    VkCheck(vkWaitForFences(context.device, 1, &f.renderFence, VK_TRUE, UINT64_MAX));
    VkCheck(vkResetFences(context.device, 1, &f.renderFence));

    VkCheck(vkAcquireNextImageKHR(context.device, context.swapchain.swapchain, UINT64_MAX, f.renderSemaphore, VK_NULL_HANDLE, &context.imageIndex));

    VkCheck(vkResetCommandBuffer(f.commandBuffer, 0));

    VkCommandBufferBeginInfo beginInfo;
    GetCommandBufferBeginInfo(&beginInfo, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
    VkCheck(vkBeginCommandBuffer(f.commandBuffer, &beginInfo));

    std::vector<VkClearValue> clears;

    VkClearValue clear;
    clear.color = { 0.1f, 0.1f, 0.1f, 1.0f };
    clears.push_back(clear);

    VkRenderPassBeginInfo renderPassInfo;
    GetRenderPassBeginInfo(&renderPassInfo, context.framebuffers[context.imageIndex], clears);
    vkCmdBeginRenderPass(f.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void EndFrame() {
    auto &f = GetFrame();

    vkCmdEndRenderPass(f.commandBuffer);

    VkCheck(vkEndCommandBuffer(f.commandBuffer));

    VkSubmitInfo submitInfo;
    GetSubmitInfo(&submitInfo, &f.commandBuffer, &f.renderSemaphore, &f.presentSemaphore);
    VkCheck(vkQueueSubmit(context.queue, 1, &submitInfo, f.renderFence));

    VkPresentInfoKHR presentInfo;
    VkResult res;
    GetPresentInfo(&presentInfo, &f.presentSemaphore, &context.imageIndex);
    presentInfo.pResults = &res;
    VkCheck(vkQueuePresentKHR(context.queue, &presentInfo));
    VkCheck(res);

    context.frameCount++;
    context.frameIndex = context.frameCount % FrameOverlap;
}
