#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "BaseModel.h"
#include "shader/Shader.h"
#include "shader/ShaderRegistry.h"
#include "texture/Texture.h"

using ModelId = std::string;

class ModelRegistry {
private:
    static ModelRegistry *_instance;

    std::unordered_map<ModelId, std::unique_ptr<BaseModel>> _models;

    void registerDefaultModels();

    friend class Application;
public:
    static ModelRegistry *get();

    void registerArrayModel(
            const ModelId &name,
            Shader *shader,
            Texture *texture,
            const std::vector<glm::vec3> &vertices,
            const std::vector<glm::vec3> &normals
    );

    void registerArrayModel(
            const ModelId &name,
            const ShaderId &shader,
            Texture *texture,
            const std::vector<glm::vec3> &vertices,
            const std::vector<glm::vec3> &normals
    );

    [[nodiscard]] BaseModel *getModel(const ModelId &name) const;

    std::vector<BaseModel *> getAll();
};
