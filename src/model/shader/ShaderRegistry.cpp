#include "ShaderRegistry.h"

#include "Shader.h"
#include "ShaderLoader.h"
#include "DefaultShaders.h"

#include "component/ShaderComponent.h"
#include "component/LightShaderComponent.h"
#include "component/TextureShaderComponent.h"
#include "component/ConstantColorShaderComponent.h"
#include "component/ModelShaderComponent.h"

ShaderRegistry *ShaderRegistry::_instance = new ShaderRegistry();

void ShaderRegistry::registerDefaultShaders() {
    registerShader(
            DefaultShaders::STANDARD,
            {
                    ModelShaderComponent::factory,
                    LightShaderComponent::factory,
                    TextureShaderComponent::factory,
                    ConstantColorShaderComponent::factory
            }
    );
    registerShader(
            DefaultShaders::CONSTANT_TEXTURE,
            {
                    TextureShaderComponent::factory
            }
    );
    registerShader(
            DefaultShaders::CONSTANT_COLOR,
            {
                    ModelShaderComponent::factory,
                    ConstantColorShaderComponent::factory
            }
    );
    registerShader(
            DefaultShaders::SKYDOME,
            {
                    TextureShaderComponent::factory
            }
    );
}

void ShaderRegistry::registerShader(const ShaderId &name) {
    registerShader(name, {});
}

void ShaderRegistry::registerShader(
        const ShaderId &name,
        const std::vector<Shader::shader_component_constructor *> &components
) {
    assert(!_shaders.contains(name) && "Shader already registered");

    auto shaderEntry = ShaderLoader::loadShader(
            SHADER_PATH + name + ".vert",
            SHADER_PATH + name + ".frag"
    );

    auto shader = new Shader(
            shaderEntry._programId,
            shaderEntry._vertexId,
            shaderEntry._fragmentId,
            components
    );
    _shaders[name] = std::unique_ptr<Shader>(shader);
}

Shader *ShaderRegistry::getShader(const ShaderId &name) {
    auto r = _shaders.find(name);

    if (r == _shaders.end()) {
        return nullptr;
    }

    return r->second.get();
}

std::vector<Shader *> ShaderRegistry::getAll() {
    std::vector<Shader *> r;
    r.reserve(_shaders.size());

    std::transform(
            _shaders.begin(),
            _shaders.end(),
            std::back_inserter(r),
            [](decltype(_shaders)::value_type &entry) {
                return entry.second.get();
            }
    );

    return r;
}

ShaderRegistry *ShaderRegistry::get() {
    return _instance;
}
