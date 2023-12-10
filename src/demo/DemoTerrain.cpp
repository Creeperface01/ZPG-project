#include "DemoTerrain.h"

#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../model/shader/DefaultShaders.h"
#include "../model/texture/DefaultTextures.h"
#include "../model/texture/TextureRegistry.h"
#include "../scene/Scene.h"
#include "../scene/light/DirectionalLightSource.h"
#include "../scene/light/SpotlightSource.h"
#include "../scene/object/component/ConstantColorObjectComponent.h"
#include "../scene/object/component/TextureObjectComponent.h"
#include "../util/math_utils.h"
#include "../window/Window.h"

Scene* DemoTerrain::create(Window* window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto textureRegistry = TextureRegistry::get();

    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);
    auto skydomeShader = ShaderRegistry::get()->getShader(DefaultShaders::SKYDOME);

    auto skydomeModel = modelRegistry->getModel(DefaultModels::SKYDOME);

    auto skydome = new DrawableObject(
        skydomeModel,
        skydomeShader,
        {
            new TextureObjectComponent(
                textureRegistry->getTexture(DefaultTextures::SKYDOME),
                false
            )
        }
    );

    scene->addBackgroundObject(skydome);

    auto terrainModel = modelRegistry->getModel(DefaultModels::TERRAIN);

    auto terrain = new DrawableObject(
        terrainModel,
        defaultShader,
        {
            new TextureObjectComponent(textureRegistry->getTexture(DefaultTextures::GRASS)),
            new ConstantColorObjectComponent(glm::vec3(86, 173, 83) / 255.f)
        }
    );
    terrain->setTranslation({0, -1, 0});

    scene->addObject(terrain);

    auto houseModel = modelRegistry->getModel(DefaultModels::HOUSE);

    auto house = new DrawableObject(
        houseModel,
        defaultShader,
        {
            new TextureObjectComponent(textureRegistry->getTexture(DefaultTextures::HOUSE))
        }
    );
    house->setTranslation({30, -1, 13});

    scene->addObject(house);

    scene->addLightSource(new DirectionalLightSource(
        glm::zero<glm::vec3>(),
        {1, 1, 1},
        0.4f,
        {0, -1, 0}
    ));

    auto suziModel = modelRegistry->getModel(DefaultModels::SUZI);

    auto suzi = new DrawableObject(
        suziModel,
        defaultShader,
        {
            new ConstantColorObjectComponent({1, 0, 0})
        }
    );

    scene->addObject(suzi);

    auto splineGenerator = math_utils::createBezierSplineGenerator(
        {1.0f, 2.0f, 0.0f},
        {2.0f, -1.0f, 0.0f},
        {3.0f, 0.0f, 0.0f},
        {4.0f, 2.0f, 0.0f}
    );

    scene->addDrawCallback([suzi, splineGenerator](Scene& scene) {
        static float t = 0;

        auto splinePos = splineGenerator(t);
        suzi->setTranslation(splinePos + glm::vec3{5, 1, 2});

        t = fmodf(t + 0.005f, 1);
    });

    auto camera = scene->getCamera();
    auto flashLight = new SpotlightSource(
        camera->getEye(),
        {1, 1, 1},
        0.f,
        camera->getDirection(),
        cosf(glm::radians(12.f)),
        cosf(glm::radians(17.f))
    );
    scene->addLightSource(flashLight);

    Keyboard::PRESS.attach([scene, flashLight](Keyboard::Press* action) {
        if (!scene->isActive()) {
            return;
        }

        if (action->_code != KeyCodes::f) {
            return;
        }

        if (flashLight->getIntensity() == 0) {
            flashLight->setIntensity(1.f);
        } else {
            flashLight->setIntensity(0.f);
        }
    });

    camera->attach([flashLight](const Camera* camera) {
        flashLight->setPosition(camera->getEye());
        flashLight->setDirection(camera->getDirection());
    });

    return scene;
}
