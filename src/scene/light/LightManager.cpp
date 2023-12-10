#include "LightManager.h"

#include "../../model/shader/ShaderRegistry.h"

LightManager::LightManager() {
    for (auto shader: ShaderRegistry::get()->getAllWithComponent<LightShaderComponent>()) {
        _lightShaders.push_back(shader);
    }
}

void LightManager::updateLights(bool force) {
    for (auto lightShader: _lightShaders) {
        lightShader->use([this, lightShader]() {
            auto component = lightShader->getComponent<LightShaderComponent>();

            component->lights.setSize(_lightSources.size());
            component->spotlights.setSize(_spotlightSources.size());
            component->directionalLights.setSize(_directionalLightSources.size());
        });
    }

    updateLights(_lightSources, force);
    updateLights(_spotlightSources, force);
    updateLights(_directionalLightSources, force);
}

void LightManager::addLight(LightSource* lightSource) {
    if (auto directionalLight = dynamic_cast<DirectionalLightSource *>(lightSource)) {
        this->_directionalLightSources.push_back(std::unique_ptr<DirectionalLightSource>(directionalLight));
    } else if (auto spotlight = dynamic_cast<SpotlightSource *>(lightSource)) {
        this->_spotlightSources.push_back(std::unique_ptr<SpotlightSource>(spotlight));
    } else {
        this->_lightSources.push_back(std::unique_ptr<LightSource>(lightSource));
    }
}

void LightManager::removeLight(LightSource* lightSource) {
    if (auto directionalLight = dynamic_cast<DirectionalLightSource *>(lightSource)) {
        // _directionalLightSources.erase(
        //     std::remove(
        //         _directionalLightSources.begin(),
        //         _directionalLightSources.end(),
        //         directionalLight
        //     ),
        //     _directionalLightSources.end()
        // );
    } else if (auto spotlight = dynamic_cast<SpotlightSource *>(lightSource)) {
        // _spotlightSources.erase(
        //     std::remove(
        //         _spotlightSources.begin(),
        //         _spotlightSources.end(),
        //         spotlight
        //     ),
        //     _spotlightSources.end()
        // );
    } else {
        // _lightSources.erase(
        //     std::remove(
        //         _lightSources.begin(),
        //         _lightSources.end(),
        //         lightSource
        //     ),
        //     _lightSources.end()
        // );
    }
}
