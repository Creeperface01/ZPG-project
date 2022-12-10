#include "ModelRegistry.h"

#include <memory>
#include <initializer_list>

#include "ArrayModel.h"
#include "DefaultModels.h"
#include "shader/DefaultShaders.h"
#include "test/ModelConverter.h"
#include "test/model/bushes.h"
#include "test/model/gift.h"
#include "test/model/plain.h"
#include "test/model/sphere.h"
#include "test/model/suzi_flat.h"
#include "test/model/suzi_smooth.h"
#include "test/model/tree.h"
#include "test/model/skycube.h"

#include "texture/Texture.h"
#include "texture/DefaultTextures.h"
#include "texture/TextureRegistry.h"

ModelRegistry *ModelRegistry::_instance = new ModelRegistry();

void ModelRegistry::registerDefaultModels() {
    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::DEFAULT);
    auto constantShader = ShaderRegistry::get()->getShader(DefaultShaders::CONSTANT);

    auto reg = [this, defaultShader](
            const ModelId &modelId,
            size_t dataSize,
            const float *data,
            Shader *shader = nullptr,
            Texture *texture = nullptr
    ) {
        std::vector<glm::vec3> vertices, normals;
        std::vector<glm::vec2> uvs;

        if(texture != nullptr) {
            ModelConverter::convert(data, dataSize, vertices, normals, uvs);
        } else {
            ModelConverter::convert(data, dataSize, vertices, normals);
        }

        if (shader == nullptr) {
            shader = defaultShader;
        }

        registerArrayModel(modelId, shader, texture, vertices, normals);
    };

    reg(DefaultModels::BUSHES, sizeof(bushes), bushes);
    reg(DefaultModels::GIFT, sizeof(gift), gift);
    reg(
            DefaultModels::PLAIN,
            sizeof(plain),
            plain
//            nullptr,
//            TextureRegistry::get()->getTexture(DefaultTextures::GRASS)
    );
    reg(DefaultModels::SPHERE, sizeof(sphere), sphere);
    reg(DefaultModels::SUZI, sizeof(suziSmooth), suziSmooth);
    reg(DefaultModels::SUZI_FLAT, sizeof(suziFlat), suziFlat);
    reg(DefaultModels::TREE, sizeof(tree), tree);
//    reg(DefaultModels::SKYCUBE, sizeof(skycube), skycube, constantShader, Texture::fromCubeMap(
//            "assets/textures/cube/posx.jpg",
//            "assets/textures/cube/negx.jpg",
//            "assets/textures/cube/posy.jpg",
//            "assets/textures/cube/negy.jpg",
//            "assets/textures/cube/posz.jpg",
//            "assets/textures/cube/negz.jpg"
//    ));

    std::vector<glm::vec3> vertices;
    ModelConverter::convertDataToVector(skycube, sizeof(skycube), vertices);

    registerArrayModel(
            DefaultModels::SKYCUBE,
            constantShader,
            TextureRegistry::get()->getTexture(DefaultTextures::SKY_BOX),
            vertices,
            vertices
    );


}

BaseModel *ModelRegistry::getModel(const ModelId &name) const {
    auto it = _models.find(name);

    if (it == _models.end()) {
        return nullptr;
    }

    return it->second.get();
}

std::vector<BaseModel *> ModelRegistry::getAll() {
    std::vector<BaseModel *> r;

    std::transform(
            _models.begin(),
            _models.end(),
            r.begin(),
            [](decltype(_models)::value_type &entry) {
                return entry.second.get();
            }
    );

    return r;
}

void ModelRegistry::registerArrayModel(
        const ModelId &name,
        Shader *shader,
        Texture *texture,
        const std::vector<glm::vec3> &vertices,
        const std::vector<glm::vec3> &normals
//        const std::vector<glm::vec2> &uvs
) {
    assert(!_models.contains(name) && "Model already registered");

    _models[name] = std::make_unique<ArrayModel>(shader,
                                                 std::initializer_list<std::vector<glm::vec3>>{vertices, normals});
}

void ModelRegistry::registerArrayModel(
        const ModelId &name,
        const ShaderId &shader,
        Texture *texture,
        const std::vector<glm::vec3> &vertices,
        const std::vector<glm::vec3> &normals
) {
    registerArrayModel(
            name,
            ShaderRegistry::get()->getShader(name),
            texture,
            vertices,
            normals
    );
}

ModelRegistry *ModelRegistry::get() {
    return _instance;
}
