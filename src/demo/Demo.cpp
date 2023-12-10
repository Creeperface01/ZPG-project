#include "Demo.h"

#include "DemoAssimp.h"
#include "DemoScene1.h"
#include "DemoScene2.h"
#include "DemoScene3.h"
#include "DemoSceneSolarSystem.h"
#include "DemoPhongCubes.h"
#include "DemoSkydome.h"
#include "DemoTerrain.h"

void Demo::initScenes(Window *window) {
    scenes.emplace_back(DemoPhongCubes::create(window));
    scenes.emplace_back(DemoScene1::create(window));
    scenes.emplace_back(DemoScene2::create(window));

    auto demoSceneSolarSystem = new DemoSceneSolarSystem();
    scenes.emplace_back(demoSceneSolarSystem->create(window));
//    scenes.push_back(std::unique_ptr<Scene>(DemoScene1::create(window)));
//    scenes.push_back(DemoScene2::create(window));

    scenes.emplace_back(DemoAssimp::create(window));
    scenes.emplace_back(DemoSkydome::create(window));
    scenes.emplace_back(DemoTerrain::create(window));

    sceneIterator = scenes.begin();
}

void Demo::run(Window *window) {
    initScenes(window);

    window->addKeyCallback([window, this](const KeyData &data) {
        if (data.action != GLFW_RELEASE || data.key != GLFW_KEY_ENTER) {
            return;
        }

        if(sceneIterator == scenes.end()) {
            sceneIterator = scenes.begin();
        }

        auto scene = sceneIterator++;
        window->setScene(scene->get());
    });
}