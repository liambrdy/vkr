#ifndef SHADER_H_
#define SHADER_H_

#include <volk.h>

#include <vector>
#include <string>
#include <unordered_map>

struct ReflectedBinding {
    uint32_t set;
    uint32_t binding;
    VkDescriptorType type;
};

struct DescriptorSetLayoutData {
    uint32_t setNumber;
    VkDescriptorSetLayoutCreateInfo createInfo;
    std::vector<VkDescriptorSetLayoutBinding> bindings;
};

struct Shader {
    VkShaderModule module;
    std::unordered_map<std::string, ReflectedBinding> bindings;
    std::vector<DescriptorSetLayoutData> layouts;
};

struct LayoutManager {
    std::unordered_map<uint32_t, VkPipelineLayout> layouts;
};

extern LayoutManager layoutManager;

VkPipelineLayout GetLayout(const std::vector<Shader> &shaders);

void ShaderCreate(Shader *shader, const std::string &path);
void ShaderDestroy(Shader *shader);

#endif // SHADER_H_
