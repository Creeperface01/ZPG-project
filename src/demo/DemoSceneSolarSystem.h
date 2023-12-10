#ifndef CV1_DEMOSCENESOLARSYSTEM_H
#define CV1_DEMOSCENESOLARSYSTEM_H


#include "../scene/Scene.h"

#include <vector>
#include <unordered_map>
#include <string>

class DemoSceneSolarSystem {
private:
    struct PlanetDefinition {
        std::string name;
        float scale;
        float radius;
        float speed;
        glm::vec3 color;
        std::vector<PlanetDefinition> moons;
    };

    std::vector<PlanetDefinition> getPlanets() const;

    // std::vector<PlanetDefinition> planetDefinitions;

    // void loadPlanetDataFromCsv();
    // std::unordered_map<std::string, PlanetDefinition> loadMoonDataFromCsv();
    // void scalePlanets();
    // void definePlanets();
public:
    Scene *create(Window *window);
};


#endif //CV1_DEMOSCENESOLARSYSTEM_H
