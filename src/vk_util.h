#ifndef VK_UTIL_H_
#define VK_UTIL_H_

#include <volk.h>

#include <string>
#include <cstdio>
#include <vector>

static inline const char* string_VkResult(VkResult input_value)
{
    switch (input_value)
    {
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
            return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
        case VK_ERROR_DEVICE_LOST:
            return "VK_ERROR_DEVICE_LOST";
        case VK_ERROR_EXTENSION_NOT_PRESENT:
            return "VK_ERROR_EXTENSION_NOT_PRESENT";
        case VK_ERROR_FEATURE_NOT_PRESENT:
            return "VK_ERROR_FEATURE_NOT_PRESENT";
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
            return "VK_ERROR_FORMAT_NOT_SUPPORTED";
        case VK_ERROR_FRAGMENTATION:
            return "VK_ERROR_FRAGMENTATION";
        case VK_ERROR_FRAGMENTED_POOL:
            return "VK_ERROR_FRAGMENTED_POOL";
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
            return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
            return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
        case VK_ERROR_INCOMPATIBLE_DRIVER:
            return "VK_ERROR_INCOMPATIBLE_DRIVER";
        case VK_ERROR_INITIALIZATION_FAILED:
            return "VK_ERROR_INITIALIZATION_FAILED";
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
            return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
            return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
            return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
        case VK_ERROR_INVALID_SHADER_NV:
            return "VK_ERROR_INVALID_SHADER_NV";
        case VK_ERROR_LAYER_NOT_PRESENT:
            return "VK_ERROR_LAYER_NOT_PRESENT";
        case VK_ERROR_MEMORY_MAP_FAILED:
            return "VK_ERROR_MEMORY_MAP_FAILED";
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
            return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
        case VK_ERROR_NOT_PERMITTED_KHR:
            return "VK_ERROR_NOT_PERMITTED_KHR";
        case VK_ERROR_OUT_OF_DATE_KHR:
            return "VK_ERROR_OUT_OF_DATE_KHR";
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
            return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
        case VK_ERROR_OUT_OF_HOST_MEMORY:
            return "VK_ERROR_OUT_OF_HOST_MEMORY";
        case VK_ERROR_OUT_OF_POOL_MEMORY:
            return "VK_ERROR_OUT_OF_POOL_MEMORY";
        case VK_ERROR_SURFACE_LOST_KHR:
            return "VK_ERROR_SURFACE_LOST_KHR";
        case VK_ERROR_TOO_MANY_OBJECTS:
            return "VK_ERROR_TOO_MANY_OBJECTS";
        case VK_ERROR_UNKNOWN:
            return "VK_ERROR_UNKNOWN";
        case VK_ERROR_VALIDATION_FAILED_EXT:
            return "VK_ERROR_VALIDATION_FAILED_EXT";
        case VK_EVENT_RESET:
            return "VK_EVENT_RESET";
        case VK_EVENT_SET:
            return "VK_EVENT_SET";
        case VK_INCOMPLETE:
            return "VK_INCOMPLETE";
        case VK_NOT_READY:
            return "VK_NOT_READY";
        case VK_OPERATION_DEFERRED_KHR:
            return "VK_OPERATION_DEFERRED_KHR";
        case VK_OPERATION_NOT_DEFERRED_KHR:
            return "VK_OPERATION_NOT_DEFERRED_KHR";
        case VK_PIPELINE_COMPILE_REQUIRED:
            return "VK_PIPELINE_COMPILE_REQUIRED";
        case VK_SUBOPTIMAL_KHR:
            return "VK_SUBOPTIMAL_KHR";
        case VK_SUCCESS:
            return "VK_SUCCESS";
        case VK_THREAD_DONE_KHR:
            return "VK_THREAD_DONE_KHR";
        case VK_THREAD_IDLE_KHR:
            return "VK_THREAD_IDLE_KHR";
        case VK_TIMEOUT:
            return "VK_TIMEOUT";
        default:
            return "Unhandled VkResult";
    }
}

#define VkCheck(x) {                                                    \
        VkResult r = x;                                                      \
        if (r != VK_SUCCESS) {                                          \
            std::printf("Vulan Error: (file '%s' line %d): %s, with code %s\n", __FILE__, __LINE__, #x, string_VkResult(r)); \
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
void GetShaderModuleCreateInfo(VkShaderModuleCreateInfo *info, const std::vector<uint32_t> &code);
void GetPipelineLayoutCreateInfo(VkPipelineLayoutCreateInfo *info, const std::vector<VkPushConstantRange> &pushConstants, const std::vector<VkDescriptorSetLayout> &layouts);
void GetPipelineCacheCreateInfo(VkPipelineCacheCreateInfo *info);

void GetGraphicsPipelineCreateInfo(VkGraphicsPipelineCreateInfo *info);
void GetPipelineShaderStageCreateInfo(VkPipelineShaderStageCreateInfo *info, VkShaderModule mod, VkShaderStageFlagBits stage);
void GetPipelineVertexInputStageCreateInfo(VkPipelineVertexInputStateCreateInfo *info, const std::vector<VkVertexInputBindingDescription> &bindings, const std::vector<VkVertexInputAttributeDescription> &attributes);
void GetPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo *info, VkPrimitiveTopology topology);
void GetPipelineTessellationStateCreateInfo(VkPipelineTessellationStateCreateInfo *info, uint32_t points);
void GetPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo *info, const VkViewport *viewport, const VkRect2D *scissor);
void GetPipelineRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateInfo *info, VkPolygonMode polygonMode, VkCullModeFlags cullMode, float lineWidth);
void GetPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo *info);
void GetPipelineDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo *info);
void GetPipelineColorBlendStateCreateInfo(VkPipelineColorBlendStateCreateInfo *info);
void GetPipelineDynamicStateCreateInfo(VkPipelineDynamicStateCreateInfo *info, const std::vector<VkDynamicState> &states);

void GetAttachmentDescription(VkAttachmentDescription *description, VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout);

void GetCommandBufferBeginInfo(VkCommandBufferBeginInfo *info, VkCommandBufferUsageFlags flags);
void GetSubmitInfo(VkSubmitInfo *info, const VkCommandBuffer *cmd, const VkSemaphore *wait, const VkSemaphore *signal);
void GetPresentInfo(VkPresentInfoKHR *info, const VkSemaphore *wait, const uint32_t *imageIndex);

void GetRenderPassBeginInfo(VkRenderPassBeginInfo *info, VkFramebuffer framebuffer, const std::vector<VkClearValue> &clears);

VkSemaphore CreateSemaphore();
VkFence CreateFence(VkFenceCreateFlags flags);

VkCommandPool CreateCommandPool(VkCommandPoolCreateFlags flags);
VkCommandBuffer CreateCommandBuffer(VkCommandPool pool);

VkShaderModule CreateShaderModule(const std::vector<uint32_t> &code);

#endif // VK_UTIL_H_
