#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Shader.h"

using ShaderId = std::string;

class ShaderRegistry {
private:
    const std::string SHADER_PATH = "assets/";

    static ShaderRegistry *_instance;

    std::unordered_map<ShaderId, std::unique_ptr<Shader>> _shaders;

    void registerDefaultShaders();

    friend class Application;

public:
    static ShaderRegistry *get();

    [[nodiscard]] Shader *getShader(const ShaderId &name);

    void registerShader(const ShaderId &name);

    std::vector<Shader *> getAll();
};
