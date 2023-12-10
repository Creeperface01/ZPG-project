//
// Created by Jan Bednář on 04.11.2023.
//

#include "DemoScene2.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include <glm/gtc/matrix_transform.hpp>

#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../scene/object/DrawableObject.h"
#include "../scene/light/LightSource.h"
#include "../scene/light/SpotlightSource.h"
#include "../scene/light/DirectionalLightSource.h"
#include "../model/shader/DefaultShaders.h"
#include "../model/texture/TextureRegistry.h"
#include "../model/texture/DefaultTextures.h"
#include "../scene/object/component/CubeMapTextureObjectComponent.h"

Scene* DemoScene2::create(Window* window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);
    auto constantShader = ShaderRegistry::get()->getShader(DefaultShaders::CONSTANT_TEXTURE);

    auto skycube = new DrawableObject(
        modelRegistry->getModel(DefaultModels::SKYCUBE),
        constantShader,
        {
            new CubeMapTextureObjectComponent(
                TextureRegistry::get()->getTexture(DefaultTextures::SKY_BOX)
            )
        }
    );
    scene->addBackgroundObject(skycube);

    auto plainModel = modelRegistry->getModel(DefaultModels::PLAIN);

    for (int x = -5; x <= 5; ++x) {
        for (int z = -5; z <= 5; ++z) {
            auto obj = new DrawableObject(plainModel, defaultShader);
            obj->setTranslation({x, -2, z});

            scene->addObject(obj);
        }
    }

    for (int x = -10; x <= 10; ++x) {
        for (int z = -10; z <= 10; ++z) {
            auto obj = new DrawableObject(plainModel, defaultShader);
            obj->setTranslation({x, -4, z});

            scene->addObject(obj);
        }
    }

    std::tuple<glm::vec3, glm::vec3> lights[] = {
        {{-3, 1, 0}, {0, 1, 0}},
        {{0,  1, -3}, {1, 0, 0}},
        {{3, 1, 0}, {0, 0, 1}},
        {{0,  1, 3},  {1, 1, 0}}
    };

    std::vector<SpotlightSource *> sources;
    for (const auto& item: lights) {
        auto direction = glm::vec3(0, 0, 0) - get<0>(item);
        direction = glm::normalize(direction);

        auto lightSource = new SpotlightSource(
            get<0>(item),
            get<1>(item),
            1,
            direction,
            cosf(glm::radians(20.f)),
            cosf(glm::radians(25.f))
        );

        sources.push_back(lightSource);

        scene->addLightSource(lightSource);
    }

    glm::vec3 direction = glm::normalize(glm::vec3(0, 0, 0) - glm::vec3(4, 5, 5));
    scene->addLightSource(new DirectionalLightSource(
        {0, 0, 0},
        {0.385, 0.647, 0.812},
        0.4f,
        direction
    ));

    auto sphereModel = modelRegistry->getModel(DefaultModels::SPHERE);

    auto sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({1, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({7, -0.5f, 7});
    scene->addObject(sphere);

    scene->addDrawCallback([sources](Scene& scene) {
        for (auto& item: sources) {
            auto rm = glm::rotate(glm::mat4(1), 0.01f, glm::vec3(0.0, 0.0, 1.0));
            auto newDirection = glm::vec3(rm * glm::vec4(item->getDirection(), 1));
            item->setDirection(newDirection);
        }
    });

    return scene;
}
