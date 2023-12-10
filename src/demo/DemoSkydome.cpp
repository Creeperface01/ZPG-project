#include "DemoSkydome.h"

#include <random>
#include <__random/random_device.h>

#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../model/shader/DefaultShaders.h"
#include "../model/texture/DefaultTextures.h"
#include "../model/texture/TextureRegistry.h"
#include "../scene/Scene.h"
#include "../scene/light/DirectionalLightSource.h"
#include "../scene/object/component/TextureObjectComponent.h"
#include "../window/Window.h"

Scene* DemoSkydome::create(Window* window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto textureRegistry = TextureRegistry::get();
    auto standardShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);
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

    auto plainModel = modelRegistry->getModel(DefaultModels::BETTER_PLAIN);

    const int floorSize = 20;
    const int step = 2;

    for (int x = -floorSize; x <= floorSize; x += step) {
        for (int z = -floorSize; z <= floorSize; z += step) {
            auto plain = new DrawableObject(
                plainModel,
                standardShader,
                {
                    new TextureObjectComponent(textureRegistry->getTexture(DefaultTextures::GRASS))
                }
            );
            plain->setTranslation({x, -1, z});
            plain->setScale({4, 1, 4});

            scene->addObject(plain);
        }
    }

    auto zombieModel = modelRegistry->getModel(DefaultModels::ZOMBIE);
    auto zombie = new DrawableObject(
        zombieModel,
        standardShader,
        {
            new TextureObjectComponent(textureRegistry->getTexture(DefaultTextures::ZOMBIE)),
        }
    );
    zombie->setTranslation({5, -1, 0});

    scene->addObject(zombie);

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> dist(-2, 2);

    std::vector<glm::vec3> treeCoordinates;

    const int treeRadius = floorSize * 4;

    for (int x = -treeRadius; x <= treeRadius; x += 8) {
        for (int z = -treeRadius; z <= treeRadius; z += 8) {
            treeCoordinates.emplace_back(
                x + dist(gen),
                -1,
                z + dist(gen)
            );
        }
    }

    auto treeModel = modelRegistry->getModel(DefaultModels::TREE);
    for (auto tree_coordinate : treeCoordinates) {
        auto tree = new DrawableObject(treeModel, standardShader);
        tree->setTranslation(tree_coordinate);
        tree->setScale({1, 5, 1});

        scene->addObject(tree);
    }

    scene->addLightSource(new DirectionalLightSource(
        glm::zero<glm::vec3>(),
        {1, 1, 1},
        0.5f,
        {0, -1, 0}
    ));

    return scene;
}
