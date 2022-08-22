#include "pipeline.h"

#include "vk_util.h"
#include "context.h"

#include <fstream>
#include <streambuf>

PipelineManager pipelineManager;

static std::vector<uint32_t> ReadShader(const std::string &path) {
    std::ifstream f(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!f.is_open()) {
        std::printf("Failed to open shader file: %s\n", path.c_str());
        std::exit(1);
    }

    size_t size = f.tellg();
    std::vector<uint32_t> code(size / sizeof(uint32_t));
    f.seekg(0);
    f.read((char *)code.data(), size);
    f.close();

    return code;
}

static VkPipelineLayout CreatePipelineLayout() {
    VkPipelineLayoutCreateInfo info;
    GetPipelineLayoutCreateInfo(&info, {}, {});

    VkPipelineLayout layout;
    VkCheck(vkCreatePipelineLayout(context.device, &info, nullptr, &layout));

    return layout;
}

static VkPipeline CreatePipeline(const PipelineInfo &info, VkPipelineLayout layout) {
    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

    Shader vertShader;
    if (pipelineManager.shaders.contains(info.vertPath)) {
        vertShader = pipelineManager.shaders.at(info.vertPath);
    } else {
        ShaderCreate(&vertShader, info.vertPath);
        pipelineManager.shaders[info.vertPath] = vertShader;
    }

    VkPipelineShaderStageCreateInfo vertInfo;
    GetPipelineShaderStageCreateInfo(&vertInfo, vertShader.module, VK_SHADER_STAGE_VERTEX_BIT);
    shaderStages.push_back(vertInfo);

    Shader fragShader;
    if (pipelineManager.shaders.contains(info.fragPath)) {
        fragShader = pipelineManager.shaders.at(info.fragPath);
    } else {
        ShaderCreate(&fragShader, info.fragPath);
        pipelineManager.shaders[info.fragPath] = fragShader;
    }

    VkPipelineShaderStageCreateInfo fragInfo;
    GetPipelineShaderStageCreateInfo(&fragInfo, fragShader.module, VK_SHADER_STAGE_FRAGMENT_BIT);
    shaderStages.push_back(fragInfo);

    std::vector<VkVertexInputBindingDescription> bindings;
    std::vector<VkVertexInputAttributeDescription> attributes;

    VkPipelineVertexInputStateCreateInfo vertexInputState;
    GetPipelineVertexInputStageCreateInfo(&vertexInputState, bindings, attributes);

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
    GetPipelineInputAssemblyStateCreateInfo(&inputAssemblyState, VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

    VkPipelineViewportStateCreateInfo viewportState;
    GetPipelineViewportStateCreateInfo(&viewportState, nullptr, nullptr);

    VkPipelineRasterizationStateCreateInfo rasterizationState;
    GetPipelineRasterizationStateCreateInfo(&rasterizationState, info.polygonMode, VK_CULL_MODE_NONE, info.lineWidth);

    std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_SCISSOR, VK_DYNAMIC_STATE_VIEWPORT};
    VkPipelineDynamicStateCreateInfo dynamicState;
    GetPipelineDynamicStateCreateInfo(&dynamicState, dynamicStates);

    VkGraphicsPipelineCreateInfo pipelineInfo;
    GetGraphicsPipelineCreateInfo(&pipelineInfo);

    pipelineInfo.stageCount = shaderStages.size();
    pipelineInfo.pStages = shaderStages.data();
    pipelineInfo.pVertexInputState = &vertexInputState;
    pipelineInfo.pInputAssemblyState = &inputAssemblyState;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizationState;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = layout;
    pipelineInfo.subpass = 0;
    pipelineInfo.renderPass = context.renderPass;

    VkPipeline pipeline;
    VkCheck(vkCreateGraphicsPipelines(context.device, pipelineManager.cache, 1, &pipelineInfo, nullptr, &pipeline));

    return pipeline;
}

void InitializePipelineManager() {
    VkPipelineCacheCreateInfo cacheInfo;
    GetPipelineCacheCreateInfo(&cacheInfo);
    VkCheck(vkCreatePipelineCache(context.device, &cacheInfo, nullptr, &pipelineManager.cache));
}

void DestroyPipelineManager() {
    vkDeviceWaitIdle(context.device);

    for (auto &[k, s] : pipelineManager.shaders)
        ShaderDestroy(&s);

    for (auto &[k, p] : pipelineManager.pipelines)
        vkDestroyPipeline(context.device, p, nullptr);

    for (auto &[k, l] : pipelineManager.layouts)
        vkDestroyPipelineLayout(context.device, l, nullptr);

    vkDestroyPipelineCache(context.device, pipelineManager.cache, nullptr);
}

VkPipeline GetPipeline(const PipelineInfo &info) {
    if (pipelineManager.pipelines.contains(info)) {
        return pipelineManager.pipelines.at(info);
    } else {
        if (pipelineManager.layouts.contains(info)) {
            VkPipeline pipeline = CreatePipeline(info, pipelineManager.layouts.at(info));
            pipelineManager.pipelines[info] = pipeline;
            return pipeline;
        }
        else {
            VkPipelineLayout layout = CreatePipelineLayout();
            VkPipeline pipeline = CreatePipeline(info, layout);
            pipelineManager.pipelines[info] = pipeline;
            pipelineManager.layouts[info] = layout;
            return pipeline;
        }
    }
}

VkPipelineLayout GetLayout(const PipelineInfo &info) {
    if (!pipelineManager.layouts.contains(info)) {
        std::printf("Layout does not exist");
        return VK_NULL_HANDLE;
    }

    return pipelineManager.layouts.at(info);
}
