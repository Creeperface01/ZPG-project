#include "ShaderRegistry.h"

#include "Shader.h"
#include "ShaderLoader.h"
#include "DefaultShaders.h"

ShaderRegistry *ShaderRegistry::_instance = new ShaderRegistry();

void ShaderRegistry::registerDefaultShaders() {
    registerShader(DefaultShaders::DEFAULT);
    registerShader(DefaultShaders::CONSTANT);
}

void ShaderRegistry::registerShader(const ShaderId &name) {
    assert(!_shaders.contains(name) && "Shader already registered");

    auto shader = ShaderLoader::loadShader(SHADER_PATH + name + ".vert", SHADER_PATH + name + ".frag");
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
