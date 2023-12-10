#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <utility>
#include <functional>

#include "Shader.h"
#include "../../util/constructor.h"

using ShaderId = std::string;

class ShaderRegistry {
private:
    const std::string SHADER_PATH = "assets/shader/";

    static ShaderRegistry *_instance;

    std::unordered_map<ShaderId, std::unique_ptr<Shader>> _shaders;

    void registerDefaultShaders();

    friend class Application;

public:
    static ShaderRegistry *get();

    [[nodiscard]] Shader *getShader(const ShaderId &name);

    void registerShader(const ShaderId &name);

    void registerShader(const ShaderId &name, const std::vector<Shader::shader_component_constructor *> &components);

    std::vector<Shader *> getAll();

    template<typename T>
    std::vector<Shader *> getAllWithComponent() {
        std::vector<Shader *> r;
        for (const auto &item: _shaders) {
            if (item.second->hasComponent<T>()) {
                r.push_back(item.second.get());
            }
        }

        return r;
    }
};
