#include "DemoAssimp.h"

#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../model/shader/DefaultShaders.h"
#include "../model/texture/DefaultTextures.h"
#include "../model/texture/TextureRegistry.h"
#include "../scene/object/component/TextureObjectComponent.h"

Scene* DemoAssimp::create(Window* window) {
    auto scene = new Scene(window);

    auto modelRegistry = ModelRegistry::get();
    auto textureRegistry = TextureRegistry::get();

    auto standardShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);

    auto houseModel = modelRegistry->getModel(DefaultModels::HOUSE);
    auto plainModel = modelRegistry->getModel(DefaultModels::PLAIN);

    auto house = new DrawableObject(
        houseModel,
        standardShader,
        {
            new TextureObjectComponent(textureRegistry->getTexture(DefaultTextures::HOUSE))
        }
    );
    house->setTranslation({0, 0, 0});

    scene->addObject(house);

    scene->addLightSource(new LightSource(
        {10, 5, 0},
        {1, 1, 1},
        0.5f
    ));

    for (int x = -10; x <= 10; x++) {
        for (int z = -10; z <= 10; z++) {
            auto plain = new DrawableObject(
                plainModel,
                standardShader
            );
            plain->setTranslation({
                x,
                -5,
                z
            });
            scene->addObject(plain);
        }
    }

    return scene;
}
