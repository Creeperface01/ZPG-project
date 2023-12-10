#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "AssimpLoader.h"
#include "BaseModel.h"
#include "texture/Texture.h"

using ModelId = std::string;

class ModelRegistry {
private:
    static ModelRegistry* _instance;

    std::unordered_map<ModelId, std::unique_ptr<BaseModel>> _models;

    AssimpLoader _assimpLoader;

    void registerDefaultModels();

    friend class Application;

public:
    static ModelRegistry* get();

    void registerArrayModel(
        const ModelId& name,
        const std::vector<ModelAttribute>& attributes
    );

    void registerElementModel(
        const ModelId& name,
        const std::vector<GLushort>& elements,
        const std::vector<ModelAttribute>& attributes
    );

    void registerObjModel(
        const ModelId& name,
        const std::string& fileName
    );

    [[nodiscard]] BaseModel* getModel(const ModelId& name) const;

    std::vector<BaseModel *> getAll();
};
