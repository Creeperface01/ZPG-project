//
// Created by Jan Bednář on 04.11.2023.
//

#include "DemoSceneSolarSystem.h"
#include "../model/DefaultModels.h"
#include "../model/ModelRegistry.h"
#include "../Application.h"
#include "../model/shader/DefaultShaders.h"
#include "../scene/object/component/ConstantColorObjectComponent.h"

#include <rapidcsv/rapidcsv.h>

#include "../model/shader/component/RotationObjectComponent.h"
#include "../util/math_utils.h"

const double KILOMETER_MILE_RATIO = 1.60934;

const double SUN_DIAMETER = 1391400;
const double SUN_SCALED_DIAMETER = 100;

const double SCALE_RATIO = SUN_SCALED_DIAMETER / SUN_DIAMETER;

const double TIME_RATIO = 86400.0 / (60 * Application::FPS);

Scene* DemoSceneSolarSystem::create(Window* window) {
    auto scene = new Scene(window);

    glm::vec3 sunColor = {1, 201 / 255.f, 23 / 255.f};

    scene->addLightSource(new LightSource(
        glm::zero<glm::vec3>(),
        sunColor,
        1
    ));

    auto modelRegistry = ModelRegistry::get();
    auto defaultShader = ShaderRegistry::get()->getShader(DefaultShaders::STANDARD);
    auto constantColorShader = ShaderRegistry::get()->getShader(DefaultShaders::CONSTANT_COLOR);

    auto sphereModel = modelRegistry->getModel(DefaultModels::SPHERE);

    auto sun = new DrawableObject(
        sphereModel,
        constantColorShader,
        {
            new ConstantColorObjectComponent(sunColor)
        }
    );
    sun->setTranslation({0.f, 2.f, 0.f});
    sun->setScale(1);
    scene->addObject(sun);

    // auto mercury = new DrawableObject(
    //     sphereModel,
    //     defaultShader,
    //     {
    //         new ConstantColorObjectComponent(mercuryColor)
    //     }
    // );
    // mercury->setScale(0.5);
    // scene->addObject(mercury);
    //
    //
    // auto mercuryMoon = new DrawableObject(
    //     sphereModel,
    //     defaultShader,
    //     {
    //         new ConstantColorObjectComponent(mercuryColor)
    //     }
    // );
    // mercuryMoon->setScale(0.1f);
    // scene->addObject(mercuryMoon);

    std::function<void(PlanetDefinition, DrawableObject*, bool)> addPlanet = [scene, sphereModel, defaultShader,
                &addPlanet](
        PlanetDefinition definition,
        DrawableObject* center,
        bool isMoon = false
    ) {
        auto rotationComponent = new RotationObjectComponent(0);

        auto planet = new DrawableObject(
            sphereModel,
            defaultShader,
            {
                new ConstantColorObjectComponent(definition.color),
                rotationComponent
            }
        );

        planet->setScale(definition.scale);

        scene->addDrawCallback([planet, center, definition, rotationComponent](Scene& scene) {
            planet->setTranslation(
                math_utils::rotate(
                    center->getTranslation(),
                    {0, 1, 0},
                    definition.radius,
                    rotationComponent->getAngle()
                )
            );

            rotationComponent->setAngle(
                rotationComponent->getAngle() + definition.speed
            );
        });

        scene->addObject(planet);

        if (!isMoon) {
            for (auto moon: definition.moons) {
                addPlanet(moon, planet, true);
            }
        }
    };

    auto planets = getPlanets();

    for (auto planetDefinition: planets) {
        addPlanet(
            planetDefinition,
            sun,
            false
        );
    }

    // addPlanet(
    //     {
    //         .name = "mercury",
    //         .scale = 0.5f,
    //         .radius = 3,
    //         .speed = 0.01f,
    //         .color = mercuryColor,
    //         .moons = {
    //             {
    //                 .name = "mercury moon 1",
    //                 .scale = 0.1f,
    //                 .radius = 1,
    //                 .speed = 0.05f,
    //                 .color = mercuryColor,
    //             }
    //         }
    //     },
    //     sun,
    //     false
    // );

    // scene->addDrawCallback([mercury, sun](Scene& scene) {
    //     static float angle = 0;
    //
    //     mercury->setTranslation(math_utils::rotate(sun->getTranslation(), {0, 1, 0}, 3, angle));
    //     angle += 0.01f;
    // });
    //
    // scene->addDrawCallback([mercuryMoon, mercury](Scene& scene) {
    //     static float angle = 0;
    //
    //     mercuryMoon->setTranslation(math_utils::rotate(mercury->getTranslation(), {0, 1, 0}, 1, angle));
    //     angle += 0.05f;
    // });


    //    for (const auto &planetDefinition: planetDefinitions) {
    //        auto planet = new DrawableObject(sphereModel);
    //        planet->setScale(static_cast<float>(planetDefinition.diameter));
    //        planet->setTranslation({planetDefinition.distanceFromSun, 0, 0});
    //
    //        auto angularVelocity = static_cast<float>(planetDefinition.angularVelocity);
    //
    //        auto orbitalCircumference = planetDefinition.distanceFromSun * 2 * M_PI;
    //        auto orbitalAngularVelocity = static_cast<float>(
    //                (orbitalCircumference / planetDefinition.orbitalVelocity) * TIME_RATIO
    //        );
    //        auto radius = static_cast<float>(planetDefinition.distanceFromSun);
    //
    //        scene->addObject(planet);
    //
    //        scene->addDrawCallback([this, planet, angularVelocity, orbitalAngularVelocity, radius](Scene &scene) {
    //            static float angle = 0;
    //            static float orbitalAngle = 0;
    //
    //            float x = radius * sinf(orbitalAngle);
    //            float z = radius * cosf(orbitalAngle);
    //
    //            planet->setTranslation({x, 0, z});
    //
    //            planet->setRotation({0, 1, 0}, angle);
    //
    //            angle += angularVelocity;
    //            orbitalAngle += orbitalAngularVelocity;
    //        });
    //    }

    return scene;
}

std::vector<DemoSceneSolarSystem::PlanetDefinition> DemoSceneSolarSystem::getPlanets() const {
    return {
        {
            .name = "mercury",
            .scale = 0.5f,
            .radius = 3,
            .speed = 0.02f,
            .color = {87 / 255.f, 60 / 255.f, 8 / 255.f},
            .moons = {
                {
                    .name = "mercury moon 1",
                    .scale = 0.1f,
                    .radius = 1,
                    .speed = 0.05f,
                    .color = {87 / 255.f, 60 / 255.f, 8 / 255.f},
                }
            }
        },
        {
            .name = "venus",
            .scale = 0.6f,
            .radius = 6,
            .speed = 0.005f,
            .color = {117 / 255.f, 91 / 255.f, 19 / 255.f},
            .moons = {
                {
                    .name = "venus moon 1",
                    .scale = 0.1f,
                    .radius = 1,
                    .speed = 0.05f,
                    .color = {87 / 255.f, 60 / 255.f, 8 / 255.f},
                }
            }
        },
        {
            .name = "earth",
            .scale = 0.8f,
            .radius = 10,
            .speed = 0.004f,
            .color = {3 / 255.f, 11 / 255.f, 64 / 255.f},
            .moons = {
                {
                    .name = "earth moon 1",
                    .scale = 0.1f,
                    .radius = 1,
                    .speed = 0.05f,
                    .color = {54 / 255.f, 53 / 255.f, 50 / 255.f},
                }
            }
        },
    };
}

// void DemoSceneSolarSystem::definePlanets() {
//    PlanetDefinition mercury = {}, venus = {}, earth = {}, mars = {}, jupiter = {}, saturn = {}, uranus = {}, neptune = {};
//
//    // Fill in the information for each planet
//    mercury.name = "Mercury";
//    mercury.diameter = 15329.0f;  // miles
//    mercury.rotationSpeed = 10.83f;  // miles/hour
//    mercury.distanceFromSun = 36.0f;  // million miles
//    mercury.orbitalSpeed = 47.87f;  // miles/second
//
//    venus.name = "Venus";
//    venus.diameter = 22362.0f;  // miles
//    venus.rotationSpeed = 6.52f;  // miles/hour
//    venus.distanceFromSun = 67.0f;  // million miles
//    venus.orbitalSpeed = 35.02f;  // miles/second
//
//    earth.name = "Earth";
//    earth.diameter = 24901.0f;  // miles
//    earth.rotationSpeed = 1037.56f;  // miles/hour
//    earth.distanceFromSun = 93.0f;  // million miles
//    earth.orbitalSpeed = 29.78f;  // kilometers/second
//    earth.moons.emplace_back(
//            "Moon",
//            10917,
//            0.0021,
//            384400,
//            1.02f
//    );
//
//    mars.name = "Mars";
//    mars.diameter = 13298.0f;  // miles
//    mars.rotationSpeed = 868.22f;  // miles/hour
//    mars.distanceFromSun = 142.0f;  // million miles
//    mars.orbitalSpeed = 24.077f;  // kilometers/second
//    mars.moons.emplace_back(
//            "Phobos",
//            69.8f,
//            0.00014088f,
//            9377.2f,
//            2.138f
//    );
//    mars.moons.emplace_back(
//            "Deimos",
//            30.3f,
//            0.00009949f,
//            23461.7f,
//            1.3513f
//    );
//
//    jupiter.name = "Jupiter";
//    jupiter.diameter = 279118.0f;  // miles
//    jupiter.rotationSpeed = 28449.55f;  // miles/hour
//    jupiter.distanceFromSun = 484.0f;  // million miles
//    jupiter.orbitalSpeed = 13.07f;  // kilometers/second
//
//    saturn.name = "Saturn";
//    saturn.diameter = 220470.0f;  // miles
//    saturn.rotationSpeed = 36099.57f;  // miles/hour
//    saturn.distanceFromSun = 886.0f;  // million miles
//    saturn.orbitalSpeed = 9.69f;  // kilometers/second
//
//    uranus.name = "Uranus";
//    uranus.diameter = 99300.0f;  // miles
//    uranus.rotationSpeed = 10380.25f;  // miles/hour
//    uranus.distanceFromSun = 1800.0f;  // million miles
//    uranus.orbitalSpeed = 6.81f;  // kilometers/second
//
//    neptune.name = "Neptune";
//    neptune.diameter = 96047.0f;  // miles
//    neptune.rotationSpeed = 10422.22f;  // miles/hour
//    neptune.distanceFromSun = 2800.0f;  // million miles
//    neptune.orbitalSpeed = 5.43f;  // kilometers/second
//
//    planetDefinitions.push_back(mercury);
//    planetDefinitions.push_back(venus);
//    planetDefinitions.push_back(earth);
//    planetDefinitions.push_back(mars);
//    planetDefinitions.push_back(jupiter);
//    planetDefinitions.push_back(saturn);
//    planetDefinitions.push_back(uranus);
//    planetDefinitions.push_back(neptune);
//
//    for (auto &item: planetDefinitions) {
//        item.diameter = item.diameter * KILOMETER_MILE_RATIO;
//        item.rotationSpeed = item.rotationSpeed * KILOMETER_MILE_RATIO;
//        item.distanceFromSun = item.distanceFromSun * KILOMETER_MILE_RATIO;
//    }
// }

// void DemoSceneSolarSystem::scalePlanets() {
//     for (auto& item: planetDefinitions) {
//         item.orbitalVelocity *= SCALE_RATIO;
//         item.diameter *= SCALE_RATIO;
//         item.distanceFromSun *= 10000 * SCALE_RATIO;
//         item.angularVelocity /= TIME_RATIO;
//     }
// }
//
// void DemoSceneSolarSystem::loadPlanetDataFromCsv() {
//     rapidcsv::Document doc("assets/data/planets.csv");
//
//     auto name = doc.GetColumn<std::string>("planet");
//     auto diameter = doc.GetColumn<float>("diameter");
//     auto rotationPeriod = doc.GetColumn<float>("rotation_period");
//     auto distanceFromSun = doc.GetColumn<float>("distance_from_sun");
//     auto orbitalVelocity = doc.GetColumn<float>("orbital_velocity");
//
//     auto rows = doc.GetRowCount();
//
//     for (size_t i = 0; i < rows; i++) {
//         auto rotationAnglePerSecond = (M_PI * 2) / (rotationPeriod[i] * 86400);
//
//         PlanetDefinition planetDefinition = {
//             name[i],
//             diameter[i],
//             rotationAnglePerSecond,
//             distanceFromSun[i],
//             orbitalVelocity[i]
//         };
//         planetDefinitions.push_back(planetDefinition);
//     }
// }
//
// std::unordered_map<std::string, DemoSceneSolarSystem::PlanetDefinition> DemoSceneSolarSystem::loadMoonDataFromCsv() {
//     rapidcsv::Document moonsDoc("assets/data/moons.csv");
//
//     auto name = moonsDoc.GetColumn<std::string>("name");
//     auto planet = moonsDoc.GetColumn<std::string>("planet");
//     auto diameter = moonsDoc.GetColumn<float>("diameter");
//     auto rotationPeriod = moonsDoc.GetColumn<float>("rotation_period");
//     auto distanceFromSun = moonsDoc.GetColumn<float>("distance_from_sun");
//     auto orbitalVelocity = moonsDoc.GetColumn<float>("orbital_velocity");
//
//     return {};
// }
