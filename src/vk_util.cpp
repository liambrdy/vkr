#include "vk_util.h"

#include "context.h"

void GetApplicationInfo(VkApplicationInfo *info, const std::string &name) {
    info->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info->pNext = nullptr;
    info->apiVersion = VK_API_VERSION_1_3;
    info->pApplicationName = name.c_str();
    info->applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info->pEngineName = "No Engine";
    info->engineVersion = VK_MAKE_VERSION(1, 0, 0);
}

void GetInstanceCreateInfo(VkInstanceCreateInfo *info, VkApplicationInfo *appInfo) {
    info->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->pApplicationInfo = appInfo;
    info->enabledLayerCount = 0;
    info->ppEnabledLayerNames = nullptr;
    info->enabledExtensionCount = 0;
    info->ppEnabledExtensionNames = nullptr;
}

void GetDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT *info, const PFN_vkDebugUtilsMessengerCallbackEXT &callback) {
    info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info->pNext = nullptr;
    info->flags = 0;
    info->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    info->pUserData = nullptr;
    info->pfnUserCallback = callback;
}

void GetQueueCreateInfo(VkDeviceQueueCreateInfo *info) {
    static float priority = 1.0f;
    info->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->pQueuePriorities = &priority;
    info->queueCount = 1;
    info->queueFamilyIndex = 0;
}

void GetDeviceCreateInfo(VkDeviceCreateInfo *info, const std::vector<const char *> &extensions, const VkPhysicalDeviceFeatures *features) {
    info->sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->pEnabledFeatures = features;
    info->enabledLayerCount = 0;
    info->ppEnabledLayerNames = nullptr;
    info->enabledExtensionCount = extensions.size();
    info->ppEnabledExtensionNames = extensions.data();
}

void GetImageViewCreateInfo(VkImageViewCreateInfo *info, VkImage image, VkFormat format, VkImageAspectFlags aspectMask) {
    info->sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->image = image;
    info->viewType = VK_IMAGE_VIEW_TYPE_2D;
    info->format = format;
    info->components.r = VK_COMPONENT_SWIZZLE_R;
    info->components.g = VK_COMPONENT_SWIZZLE_G;
    info->components.b = VK_COMPONENT_SWIZZLE_B;
    info->components.a = VK_COMPONENT_SWIZZLE_A;
    info->subresourceRange.aspectMask = aspectMask;
    info->subresourceRange.baseMipLevel = 0;
    info->subresourceRange.levelCount = 1;
    info->subresourceRange.baseArrayLayer = 0;
    info->subresourceRange.layerCount = 1;
}

void GetSwapchainCreateInfo(VkSwapchainCreateInfoKHR *info) {
    info->sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info->pNext = nullptr;
    info->flags = 0;
    info->surface = context.surface;
    info->imageArrayLayers = 1;
    info->imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    info->imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    info->queueFamilyIndexCount = 0;
    info->pQueueFamilyIndices = nullptr;
    info->preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    info->compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info->clipped = VK_TRUE;
    info->oldSwapchain = VK_NULL_HANDLE;
}

void GetSemaphoreCreateInfo(VkSemaphoreCreateInfo *info) {
    info->sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
}

void GetFenceCreateInfo(VkFenceCreateInfo *info, VkFenceCreateFlags flags) {
    info->sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = flags;
}

void GetRenderPassCreateInfo(VkRenderPassCreateInfo *info, const std::vector<VkAttachmentDescription> &attachments, const std::vector<VkSubpassDescription> &subpasses, const std::vector<VkSubpassDependency> &dependencies)  {
    info->sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->attachmentCount = attachments.size();
    info->pAttachments = attachments.data();
    info->subpassCount = subpasses.size();
    info->pSubpasses = subpasses.data();
    info->dependencyCount = dependencies.size();
    info->pDependencies = dependencies.data();
}

void GetFramebufferCreateInfo(VkFramebufferCreateInfo *info) {
    info->sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->renderPass = context.renderPass;
    info->width = context.swapchain.extent.width;
    info->height = context.swapchain.extent.height;
    info->layers = 1;
}

void GetCommandPoolCreateInfo(VkCommandPoolCreateInfo *info, VkCommandPoolCreateFlags flags) {
    info->sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = flags;
    info->queueFamilyIndex = 0;
}

void GetCommandBufferAllocInfo(VkCommandBufferAllocateInfo *info, VkCommandPool pool, uint32_t count) {
    info->sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    info->pNext = nullptr;
    info->commandBufferCount = count;
    info->commandPool = pool;
    info->level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
}

void GetAttachmentDescription(VkAttachmentDescription *description, VkFormat format, VkImageLayout initialLayout, VkImageLayout finalLayout) {
    description->flags = 0;
    description->format = format;
    description->samples = VK_SAMPLE_COUNT_1_BIT;
    description->loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    description->storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    description->stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    description->stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    description->initialLayout = initialLayout;
    description->finalLayout = finalLayout;
}

void GetCommandBufferBeginInfo(VkCommandBufferBeginInfo *info, VkCommandBufferUsageFlags flags) {
    info->sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info->pNext = nullptr;
    info->flags = flags;
    info->pInheritanceInfo = nullptr;
}

void GetSubmitInfo(VkSubmitInfo *info, const VkCommandBuffer *cmd, const VkSemaphore *wait, const VkSemaphore *signal) {
    static VkPipelineStageFlags dstFlag = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    info->sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info->pNext = nullptr;
    info->waitSemaphoreCount = 1;
    info->pWaitSemaphores = wait;
    info->pWaitDstStageMask = &dstFlag;
    info->commandBufferCount = 1;
    info->pCommandBuffers = cmd;
    info->signalSemaphoreCount = 1;
    info->pSignalSemaphores = signal;
}

void GetPresentInfo(VkPresentInfoKHR *info, const VkSemaphore *wait, const uint32_t *imageIndex) {
    info->sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info->pNext = nullptr;
    info->waitSemaphoreCount = 1;
    info->pWaitSemaphores = wait;
    info->swapchainCount = 1;
    info->pSwapchains = &context.swapchain.swapchain;
    info->pImageIndices = imageIndex;
    info->pResults = nullptr;
}

void GetRenderPassBeginInfo(VkRenderPassBeginInfo *info, VkFramebuffer framebuffer, const std::vector<VkClearValue> &clears) {
    info->sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info->pNext = nullptr;
    info->renderPass = context.renderPass;
    info->framebuffer = framebuffer;
    info->renderArea.offset = {0, 0};
    info->renderArea.extent = {context.swapchain.extent.width, context.swapchain.extent.height};
    info->clearValueCount = clears.size();
    info->pClearValues = clears.data();
}

VkSemaphore CreateSemaphore() {
    VkSemaphoreCreateInfo info;
    GetSemaphoreCreateInfo(&info);

    VkSemaphore semaphore;
    VkCheck(vkCreateSemaphore(context.device, &info, nullptr, &semaphore));

    return semaphore;
}

VkFence CreateFence(VkFenceCreateFlags flags) {
    VkFenceCreateInfo info;
    GetFenceCreateInfo(&info, flags);

    VkFence fence;
    VkCheck(vkCreateFence(context.device, &info, nullptr, &fence));

    return fence;
}

VkCommandPool CreateCommandPool(VkCommandPoolCreateFlags flags) {
    VkCommandPoolCreateInfo info;
    GetCommandPoolCreateInfo(&info, flags);

    VkCommandPool pool;
    VkCheck(vkCreateCommandPool(context.device, &info, nullptr, &pool));

    return pool;
}

VkCommandBuffer CreateCommandBuffer(VkCommandPool pool) {
    VkCommandBufferAllocateInfo info;
    GetCommandBufferAllocInfo(&info, pool, 1);

    VkCommandBuffer cmd;
    VkCheck(vkAllocateCommandBuffers(context.device, &info, &cmd));

    return cmd;
}
