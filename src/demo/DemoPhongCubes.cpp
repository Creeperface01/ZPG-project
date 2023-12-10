#include "DemoPhongCubes.h"

#include "../model/shader/DefaultShaders.h"
#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../window/Window.h"
#include "../io/Keyboard.h"

#include <vector>

Scene *DemoPhongCubes::create(Window *window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);

    auto sphereModel = modelRegistry->getModel(DefaultModels::SPHERE);

    scene->addLightSource(new LightSource(
            glm::zero<glm::vec3>(),
            {1, 1, 1},
            1
    ));

    std::vector<glm::vec3> cubePositions = {
            {-2, 0, 0},
            {2, 0, 0},
            {0, 2, 0},
            {0, -2, 0}
    };

    for (const auto &item: cubePositions) {
        auto sphere = new DrawableObject(sphereModel, defaultShader);
        sphere->setTranslation(item);

        scene->addObject(sphere);
    }

//    Keyboard::RELEASE.attach([scene](const auto action) {
//        if(!scene->isActive()) {
//            return;
//        }
//
//        if(action->_code != KeyCodes::k) {
//            return;
//        }
//    });

    auto camera = scene->getCamera();
    camera->setEye({0, 0, -7});
    camera->pointAt({0, 0, 0});

    return scene;
}
