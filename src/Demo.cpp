#include "Demo.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>
#include <glm/gtc/matrix_transform.hpp>

#include "model/DefaultModels.h"
#include "model/ModelRegistry.h"
#include "scene/DrawableObject.h"
#include "scene/LightSource.h"
#include "scene/SpotlightSource.h"
#include "scene/DirectionalLightSource.h"

int sceneIndex = 0;
std::vector<Scene *> scenes;

Scene *createScene1(Window *window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();

    auto plainModel = modelRegistry->getModel(DefaultModels::PLAIN);

    for (int x = -5; x <= 5; ++x) {
        for (int z = -5; z <= 5; ++z) {
            auto obj = new DrawableObject(plainModel);
            obj->setPosition({x, -2, z});

            scene->addObject(obj);
        }
    }

    auto sphereModel = modelRegistry->getModel(DefaultModels::SPHERE);

    auto sphere = new DrawableObject(sphereModel);
    sphere->setPosition({-3, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel);
    sphere->setPosition({3, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel);
    sphere->setPosition({0, -0.5f, -3});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel);
    sphere->setPosition({0, -0.5f, 3});
    scene->addObject(sphere);

    auto suziFlat = new DrawableObject(modelRegistry->getModel(DefaultModels::SUZI));
    suziFlat->setPosition({7, 5, 7});
    scene->addObject(suziFlat);

    auto suziSmooth = new DrawableObject(modelRegistry->getModel(DefaultModels::SUZI_FLAT));
//    suziSmooth->setScale(glm::vec3(10, 10, 10));
    suziSmooth->setPosition({-2, 1, -2});
    scene->addObject(suziSmooth);

    auto tree = new DrawableObject(modelRegistry->getModel(DefaultModels::TREE));
    tree->setPosition({5, -2, 5});
    scene->addObject(tree);

    scene->addLightSource(new LightSource({2, 3, 2}, {0.385, 0.647, 0.812}, 0.4));

    scene->addLightSource(new SpotlightSource({0, 10, 0}, {1, 0, 0}, 1, {0, -1, 0}, 12.5, 17.5));

    scene->addDrawCallback([suziSmooth, tree](Scene &scene) {
        static float angle = 0;

//        tree->setRotation({0, 1, 0}, {5, -2, 5}, angle);
        tree->setRotation({0, 1, 0}, angle);

        angle += 0.01f;
    });

    return scene;
}

Scene *createScene2(Window *window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();

    auto skycube = new DrawableObject(modelRegistry->getModel(DefaultModels::SKYCUBE));
    scene->addBackgroundObject(skycube);

    auto plainModel = modelRegistry->getModel(DefaultModels::PLAIN);

    for (int x = -5; x <= 5; ++x) {
        for (int z = -5; z <= 5; ++z) {
            auto obj = new DrawableObject(plainModel);
            obj->setPosition({x, -2, z});

            scene->addObject(obj);
        }
    }

    for (int x = -10; x <= 10; ++x) {
        for (int z = -10; z <= 10; ++z) {
            auto obj = new DrawableObject(plainModel);
            obj->setPosition({x, -4, z});

            scene->addObject(obj);
        }
    }

    std::tuple<glm::vec3, glm::vec3> lights[] = {
            {{-3, 1, 0},  {0, 1, 0}},
            {{0,  1, -3}, {1, 0, 0}},
            {{3,  1, 0},  {0, 0, 1}},
            {{0,  1, 3},  {1, 1, 0}}
    };

    std::vector<SpotlightSource *> sources;
    for (const auto &item: lights) {
        auto direction = glm::vec3(0, 0, 0) - get<0>(item);
        direction = glm::normalize(direction);

        auto lightSource = new SpotlightSource(
                get<0>(item),
                get<1>(item),
                1,
                direction,
                10,
                14
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

    auto sphere = new DrawableObject(sphereModel);
    sphere->setPosition({1, -0.5f, 0});
    scene->addObject(sphere);

    sphere = new DrawableObject(sphereModel);
    sphere->setPosition({7, -0.5f, 7});
    scene->addObject(sphere);

//    scene->addDrawCallback([sources](Scene &scene) {
//        for (auto &item: sources) {
//            auto rm = glm::rotate(glm::mat4(1), 0.01f, glm::vec3(0.0, 0.0, 1.0));
//            auto newDirection = glm::vec3(rm * glm::vec4(item->getDirection(), 1));
//            item->setDirection(newDirection);
//        }
//
//        scene.updateLights();
//    });

    return scene;
}

void initScenes(Window *window) {
    scenes.push_back(createScene1(window));
    scenes.push_back(createScene2(window));
}

void Demo::run(Window *window) {
    initScenes(window);

    window->addKeyCallback([window](const KeyData &data) {
        if (data.action != GLFW_RELEASE || data.key != GLFW_KEY_ENTER) {
            return;
        }

        auto scene = scenes[(sceneIndex++) % scenes.size()];
        window->setScene(scene);
    });
}
