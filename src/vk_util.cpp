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

void GetShaderModuleCreateInfo(VkShaderModuleCreateInfo *info, const std::vector<uint32_t> &code) {
    info->sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->codeSize = code.size() * sizeof(uint32_t);
    info->pCode = code.data();
}

void GetPipelineLayoutCreateInfo(VkPipelineLayoutCreateInfo *info, const std::vector<VkPushConstantRange> &pushConstants, const std::vector<VkDescriptorSetLayout> &layouts) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->pushConstantRangeCount = pushConstants.size();
    info->pPushConstantRanges = pushConstants.data();
    info->setLayoutCount = layouts.size();;
    info->pSetLayouts = layouts.data();
}

void GetPipelineCacheCreateInfo(VkPipelineCacheCreateInfo *info) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->initialDataSize = 0;
    info->pInitialData = nullptr;
}

void GetGraphicsPipelineCreateInfo(VkGraphicsPipelineCreateInfo *info) {
    static VkPipelineMultisampleStateCreateInfo multisampleState;
    GetPipelineMultisampleStateCreateInfo(&multisampleState);

    static VkPipelineDepthStencilStateCreateInfo depthStencilState;
    GetPipelineDepthStencilStateCreateInfo(&depthStencilState);

    static VkPipelineColorBlendStateCreateInfo blendState;
    GetPipelineColorBlendStateCreateInfo(&blendState);

    info->sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->pTessellationState = nullptr;
    info->pMultisampleState = &multisampleState;
    info->pDepthStencilState = &depthStencilState;
    info->pColorBlendState = &blendState;
    info->basePipelineHandle = VK_NULL_HANDLE;
    info->basePipelineIndex = 0;
}

void GetPipelineShaderStageCreateInfo(VkPipelineShaderStageCreateInfo *info, VkShaderModule mod, VkShaderStageFlagBits stage) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->stage = stage;
    info->module = mod;
    info->pName = "main";
    info->pSpecializationInfo = nullptr;
}

void GetPipelineVertexInputStageCreateInfo(VkPipelineVertexInputStateCreateInfo *info, const std::vector<VkVertexInputBindingDescription> &bindings, const std::vector<VkVertexInputAttributeDescription> &attributes) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->vertexBindingDescriptionCount = bindings.size();
    info->pVertexBindingDescriptions = bindings.data();
    info->vertexAttributeDescriptionCount = attributes.size();
    info->pVertexAttributeDescriptions = attributes.data();
}

void GetPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo *info, VkPrimitiveTopology topology) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->topology = topology;
    info->primitiveRestartEnable = VK_FALSE;
}

void GetPipelineTessellationStateCreateInfo(VkPipelineTessellationStateCreateInfo *info, uint32_t points) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->patchControlPoints = points;
}

void GetPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo *info, const VkViewport *viewport, const VkRect2D *scissor) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->viewportCount = 1;
    info->pViewports = viewport;
    info->scissorCount = 1;
    info->pScissors = scissor;
}

void GetPipelineRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateInfo *info, VkPolygonMode polygonMode, VkCullModeFlags cullMode, float lineWidth) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->depthClampEnable = VK_FALSE;
    info->rasterizerDiscardEnable = VK_FALSE;
    info->polygonMode = polygonMode;
    info->cullMode = cullMode;
    info->frontFace = VK_FRONT_FACE_CLOCKWISE;
    info->depthBiasEnable = VK_FALSE;
    info->depthBiasConstantFactor = 0.0f;
    info->depthBiasClamp = 0.0f;
    info->depthBiasSlopeFactor = 0.0f;
    info->lineWidth = lineWidth;
}

void GetPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo *info) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    info->sampleShadingEnable = VK_FALSE;
    info->minSampleShading = 0.0f;
    info->pSampleMask = nullptr;
    info->alphaToCoverageEnable = VK_FALSE;
    info->alphaToOneEnable = VK_FALSE;
}

void GetPipelineDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateInfo *info) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->depthTestEnable = VK_TRUE;
    info->depthWriteEnable = VK_TRUE;
    info->depthCompareOp = VK_COMPARE_OP_LESS;
    info->depthBoundsTestEnable = VK_FALSE;
    info->stencilTestEnable = VK_FALSE;
    info->minDepthBounds = 0.0f;
    info->maxDepthBounds = 0.0f;
}

void GetPipelineColorBlendStateCreateInfo(VkPipelineColorBlendStateCreateInfo *info) {
    static VkPipelineColorBlendAttachmentState attachment;
    attachment.blendEnable = VK_TRUE;
    attachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    attachment.colorBlendOp = VK_BLEND_OP_ADD;
    attachment.alphaBlendOp = VK_BLEND_OP_ADD;
    attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    info->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->logicOpEnable = VK_FALSE;
    info->logicOp = VK_LOGIC_OP_COPY;
    info->attachmentCount = 1;
    info->pAttachments = &attachment;
    info->blendConstants[0] = 0.0f;
    info->blendConstants[1] = 0.0f;
    info->blendConstants[2] = 0.0f;
    info->blendConstants[3] = 0.0f;
}

void GetPipelineDynamicStateCreateInfo(VkPipelineDynamicStateCreateInfo *info, const std::vector<VkDynamicState> &states) {
    info->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    info->pNext = nullptr;
    info->flags = 0;
    info->dynamicStateCount = states.size();
    info->pDynamicStates = states.data();
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

VkShaderModule CreateShaderModule(const std::vector<uint32_t> &code) {
    VkShaderModuleCreateInfo moduleInfo;
    GetShaderModuleCreateInfo(&moduleInfo, code);

    VkShaderModule mod;
    VkCheck(vkCreateShaderModule(context.device, &moduleInfo, nullptr, &mod));

    return mod;
}
