#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>

#include <shaderc/shaderc.hpp>
#include <spirv_reflect.h>

#include "vk_util.h"
#include "context.h"

LayoutManager layoutManager;

static std::string ReadShader(const std::string &path) {
    std::ifstream f(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!f.is_open()) {
        std::printf("Failed to open shader file: %s\n", path.c_str());
        std::exit(1);
    }

    std::string source;
    size_t size = f.tellg();
    source.resize(size);
    f.seekg(0);
    f.read(source.data(), size);
    f.close();

    return source;
}

static std::vector<uint32_t> CompileShader(const std::string &source, shaderc_shader_kind stage, const std::string &name) {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    options.SetOptimizationLevel(shaderc_optimization_level_performance);

    shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source.c_str(), stage, name.c_str(), options);

    return {module.cbegin(), module.cend()};
}

static std::vector<uint32_t> LoadAndCompileShader(const std::string &path) {
    std::string name = path.substr(path.find_last_of("/"));
    name = name.substr(0, name.find('.'));

    auto &&extensionToShaderKind = [](const std::string &path) -> shaderc_shader_kind {
        auto extension = path.substr(path.find_last_of('.') + 1);
        if (extension == "vert") return shaderc_vertex_shader;
        else if (extension == "frag") return shaderc_fragment_shader;
        else if (extension == "comp") return shaderc_compute_shader;
        else return (shaderc_shader_kind)0;
    };

    shaderc_shader_kind stage = extensionToShaderKind(path);

    auto source = ReadShader(path);
    auto code = CompileShader(source, stage, name);

    return code;
}

void ShaderCreate(Shader *shader, const std::string &path) {
    auto code = LoadAndCompileShader(path);

    VkShaderModule module = CreateShaderModule(code);
    shader->module = module;

    SpvReflectShaderModule spvModule;
    spvReflectCreateShaderModule(code.size() * sizeof(uint32_t), code.data(), &spvModule);

    uint32_t count = 0;
    spvReflectEnumerateDescriptorSets(&spvModule, &count, nullptr);
    std::vector<SpvReflectDescriptorSet *> sets(count);
    spvReflectEnumerateDescriptorSets(&spvModule, &count, sets.data());

    for (uint32_t i = 0; i < count; i++) {
        const SpvReflectDescriptorSet set = *(sets[i]);

        DescriptorSetLayoutData layout;
        layout.bindings.resize(set.binding_count);

        for (uint32_t j = 0; j < set.binding_count; j++) {
            const SpvReflectDescriptorBinding binding = *(set.bindings[j]);

            VkDescriptorSetLayoutBinding layoutBinding;
            layoutBinding.binding = binding.binding;
            layoutBinding.descriptorType = (VkDescriptorType)binding.descriptor_type;
            layoutBinding.descriptorCount = 1;
            for (uint32_t dim = 0; dim < binding.array.dims_count; dim++)
                layoutBinding.descriptorCount *= binding.array.dims[dim];
            layoutBinding.stageFlags = (VkShaderStageFlags)spvModule.shader_stage;
            layout.bindings[j] = layoutBinding;

            ReflectedBinding reflBinding;
            reflBinding.binding = layoutBinding.binding;
            reflBinding.set = set.set;
            reflBinding.type = layoutBinding.descriptorType;

            shader->bindings[binding.name] = reflBinding;
        }

        layout.setNumber = set.set;
        layout.createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout.createInfo.pNext = nullptr;
        layout.createInfo.flags = 0;
        layout.createInfo.bindingCount = layout.bindings.size();
        layout.createInfo.pBindings = layout.bindings.data();

        shader->layouts.push_back(layout);
    }

    spvReflectDestroyShaderModule(&spvModule);
}

void ShaderDestroy(Shader *shader) {
    vkDestroyShaderModule(context.device, shader->module, nullptr);
}

constexpr uint32_t fnv1a_32(char const* s, std::size_t count)
{
    return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
}

uint32_t HashLayoutCreateInfo(VkPipelineLayoutCreateInfo *info) {
    std::stringstream ss;

    ss << info->flags;

    for (uint32_t i = 0; i < info->pushConstantRangeCount; i++) {
        ss << info->pPushConstantRanges[i].stageFlags;
        ss << info->pPushConstantRanges[i].size;
        ss << info->pPushConstantRanges[i].offset;
    }

    for (uint32_t i = 0; i < info->setLayoutCount; i++) {

    }

    auto str = ss.str(0;)
}

VkPipelineLayout GetLayout(const std::vector<Shader> &shaders) {

}
