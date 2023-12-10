#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H
#include <unordered_map>
#include <vector>

#include "DirectionalLightSource.h"
#include "LightSource.h"
#include "SpotlightSource.h"
#include "../../model/shader/Shader.h"

class LightManager {
private:
    std::pmr::vector<Shader *> _lightShaders;

    std::vector<std::unique_ptr<LightSource>> _lightSources;
    std::vector<std::unique_ptr<SpotlightSource>> _spotlightSources;
    std::vector<std::unique_ptr<DirectionalLightSource>> _directionalLightSources;

    template<typename T>
    void updateLights(std::vector<std::unique_ptr<T>>& lights, bool force = false) {
        std::unordered_map<size_t, T *> lightsToUpdate;
        for (size_t i = 0; i < lights.size(); ++i) {
            auto light = lights[i].get();

            if (!light->isDirty() && !force) {
                continue;
            }

            lightsToUpdate.insert({i, light});
            light->setDirty(true);
        }

        if (lightsToUpdate.empty()) {
            return;
        }

        for (auto lightShader: _lightShaders) {
            lightShader->use([this, lightShader, lightsToUpdate]() {
                auto component = lightShader->getComponent<LightShaderComponent>();

                for (auto& [index, lightSource]: lightsToUpdate) {
                    lightSource->updateShader(index, component);
                }
            });
        }
    }

public:
    LightManager();

    void updateLights(bool force);

    void addLight(LightSource* lightSource);

    void removeLight(LightSource* lightSource);
};


#endif //LIGHTMANAGER_H
