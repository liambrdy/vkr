#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <volk.h>

#include <map>
#include <unordered_map>
#include <string>
#include <vector>

#include "shader.h"

struct PipelineInfo {
    std::string vertPath, fragPath;
    VkPolygonMode polygonMode;
    float lineWidth;

    bool const operator==(const PipelineInfo &info) const {
        return std::make_tuple(vertPath, fragPath, polygonMode, lineWidth) == std::make_tuple(info.vertPath, info.fragPath, info.polygonMode, info.lineWidth);
    }

    bool operator<(const PipelineInfo &info) const {
        return std::make_tuple(vertPath, fragPath, polygonMode, lineWidth) < std::make_tuple(info.vertPath, info.fragPath, info.polygonMode, info.lineWidth);
    }
};

struct PipelineManager {
    std::map<PipelineInfo, VkPipeline> pipelines;

    std::map<std::string, Shader> shaders;

    VkPipelineCache cache;
};

extern PipelineManager pipelineManager;

void InitializePipelineManager();
void DestroyPipelineManager();

VkPipeline GetPipeline(const PipelineInfo &info);
VkPipelineLayout GetLayout(const PipelineInfo &info);

#endif // PIPELINE_H_
