//
// Created by Jan Bednář on 04.11.2023.
//

#include "DemoScene1.h"

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

Scene* DemoScene1::create(Window* window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);

    auto plainModel = modelRegistry->getModel(DefaultModels::PLAIN);

    for (int x = -5; x <= 5; ++x) {
        for (int z = -5; z <= 5; ++z) {
            auto obj = new DrawableObject(plainModel, defaultShader);
            obj->setTranslation({x, -2, z});

            scene->addObject(obj);
        }
    }

    auto sphereModel = modelRegistry->getModel(DefaultModels::SPHERE);

    auto sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({-3, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({3, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({0, -0.5f, -3});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel, defaultShader);
    sphere->setTranslation({0, -0.5f, 3});
    scene->addObject(sphere);

    auto sphere2 = new DrawableObject(sphereModel, defaultShader);
    sphere2->setTranslation({0, -0.5f, 3});
    sphere2->setScale(0.5f);
    scene->addObject(sphere2);

    auto suziFlat = new DrawableObject(modelRegistry->getModel(DefaultModels::SUZI), defaultShader);
    suziFlat->setTranslation({7, 5, 7});
    scene->addObject(suziFlat);

    auto suziSmooth = new DrawableObject(modelRegistry->getModel(DefaultModels::SUZI_FLAT), defaultShader);
    //    suziSmooth->setScale(glm::vec3(10, 10, 10));
    suziSmooth->setTranslation({-2, 1, -2});
    scene->addObject(suziSmooth);

    auto tree = new DrawableObject(modelRegistry->getModel(DefaultModels::TREE), defaultShader);
    tree->setTranslation({0, -2, 0});
    scene->addObject(tree);

    scene->addLightSource(new LightSource({2, 3, 2}, {0.385, 0.647, 0.812}, 0.4));

    scene->addLightSource(
        new SpotlightSource(
            {0, 10, 0},
            {1, 0, 0},
            1,
            {0, -1, 0},
            12.5,
            17.5
        )
    );

    scene->addDrawCallback([sphere2, tree](Scene& scene) {
        static float angle = 0;
        static float radius = 3;

        static float angle2 = 0;
        static float radius2 = 10;

        //        tree->setRotation({0, 1, 0}, {5, -2, 5}, angle);
        float x = radius * sinf(angle);
        float z = radius * cosf(angle);

        //        tree->setTranslation({x, -2, z});
        tree->setRotation({0, 1, 0}, 0, angle);

        float x2 = radius2 * sinf(angle2);
        float z2 = radius2 * cosf(angle2);

        //        sphere2->setTranslation({x + 1 + x2, 0, z + 1 + z2});
        sphere2->setTranslation({x2, 0, z2});

        angle += 0.01f;
        angle2 -= 0.05f;
    });

    return scene;
}
