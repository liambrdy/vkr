#ifndef VK_UTIL_H_
#define VK_UTIL_H_

#include <volk.h>

#include <string>
#include <cstdio>
#include <vector>

#define VkCheck(x) {                                                    \
        int r = x;                                                      \
        if (r != VK_SUCCESS) {                                          \
            std::printf("Vulan Error: (file '%s' line %d): %s, with code %d", __FILE__, __LINE__, #x, r); \
        }                                                               \
    }

void GetApplicationInfo(VkApplicationInfo *info, const std::string &name);
void GetInstanceCreateInfo(VkInstanceCreateInfo *info, VkApplicationInfo *appInfo);
void GetDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT *info, const PFN_vkDebugUtilsMessengerCallbackEXT &callback);
void GetQueueCreateInfo(VkDeviceQueueCreateInfo *info);
void GetDeviceCreateInfo(VkDeviceCreateInfo *info, const std::vector<const char *> &extensions, const VkPhysicalDeviceFeatures *features);
void GetImageViewCreateInfo(VkImageViewCreateInfo *info, VkImage image, VkFormat format, VkImageAspectFlags aspectMask);
void GetSwapchainCreateInfo(VkSwapchainCreateInfoKHR *info);
void GetSemaphoreCreateInfo(VkSemaphoreCreateInfo *info);
void GetFenceCreateInfo(VkFenceCreateInfo *info, VkFenceCreateFlags flags);
void GetRenderPassCreateInfo(VkRenderPassCreateInfo *info, const std::vector<VkAttachmentDescription> &attachments, const std::vector<VkSubpassDescription> &subpasses, const std::vector<VkSubpassDependency> &dependencies);
void GetFramebufferCreateInfo(VkFramebufferCreateInfo *info);
void GetCommandPoolCreateInfo(VkCommandPoolCreateInfo *info, VkCommandPoolCreateFlags flags);
void GetCommandBufferAllocInfo(VkCommandBufferAllocateInfo *info);

void GetAttachmentDescription(VkAttachmentDescription *description, VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout);

void GetCommandBufferBeginInfo(VkCommandBufferBeginInfo *info, VkCommandBufferUsageFlags flags);
void GetSubmitInfo(VkSubmitInfo *info, const VkCommandBuffer *cmd, const VkSemaphore *wait, const VkSemaphore *signal);
void GetPresentInfo(VkPresentInfoKHR *info, const VkSemaphore *wait, const uint32_t *imageIndex);

void GetRenderPassBeginInfo(VkRenderPassBeginInfo *info, VkFramebuffer framebuffer, const std::vector<VkClearValue> &clears);

VkSemaphore CreateSemaphore();
VkFence CreateFence(VkFenceCreateFlags flags);

VkCommandPool CreateCommandPool(VkCommandPoolCreateFlags flags);
VkCommandBuffer CreateCommandBuffer(VkCommandPool pool);

#endif // VK_UTIL_H_
