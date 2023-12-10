#include "Shader.h"

#include "../../util/debug.h"
#include "../../scene/light/SpotlightSource.h"
#include "../../scene/light/DirectionalLightSource.h"

#include <glm/gtc/matrix_transform.hpp>

Shader::Shader(
        GLuint programId,
        GLuint vertexId,
        GLuint fragmentId
) : _programId(programId),
    _vertexId(vertexId),
    _fragmentId(fragmentId) {

//    for (int i = 0; i < MAX_LIGHTS; ++i) {
//        lights.emplace_back(_programId, "lights", i);
//        spotlights.emplace_back(_programId, "spotlights", i);
//        directionalLights.emplace_back(_programId, "directionalLights", i);
//    }

//    lights.reserve(MAX_LIGHTS);
//    spotlights.reserve(MAX_LIGHTS);
}

Shader::Shader(
        GLuint programId,
        GLuint vertexId,
        GLuint fragmentId,
        const std::vector<shader_component_constructor *> &componentFactories
) : Shader(programId, vertexId, fragmentId) {
    for (const auto &item: componentFactories) {
        this->_components.emplace_back(item(this));
    }
}

Shader::~Shader() {
    debugGlCall(glDetachShader, _programId, _vertexId);
    debugGlCall(glDetachShader, _programId, _fragmentId);
    debugGlCall(glDeleteShader, _vertexId);
    debugGlCall(glDeleteShader, _fragmentId);
    debugGlCall(glUseProgram, 0);
    debugGlCall(glDeleteProgram, _programId);
}

void Shader::startUsing() {
    debugGlCall(glUseProgram, _programId);
}

void Shader::stopUsing() {
    debugGlCall(glUseProgram, 0);
}

//void Shader::setLightArray(const std::vector<LightSource *> &lightSources) {
//    assert(lightSources.size() <= MAX_LIGHTS && "Max light sources count exceeded");
//
//    std::vector<const LightSource *> lights;
//    std::vector<const LightSource *> directionalLights;
//    std::vector<const LightSource *> spotlights;
//
//    std::copy_if(
//            lightSources.begin(),
//            lightSources.end(),
//            std::back_inserter(lights),
//            [](const LightSource *source) {
//                return !dynamic_cast<const SpotlightSource *>(source)
//                       && !dynamic_cast<const DirectionalLightSource *>(source);
//            }
//    );
//
//    std::copy_if(
//            lightSources.begin(),
//            lightSources.end(),
//            std::back_inserter(directionalLights),
//            [](const LightSource *source) { return dynamic_cast<const DirectionalLightSource *>(source); }
//    );
//
//    std::copy_if(
//            lightSources.begin(),
//            lightSources.end(),
//            std::back_inserter(spotlights),
//            [](const LightSource *source) { return dynamic_cast<const SpotlightSource *>(source); }
//    );
//
//    _lightsSize = lights.size();
//    for (int i = 0; i < lights.size(); ++i) {
//        auto source = lights[i];
//        auto &light = this->lights[i];
//
//        light.color = source->getColor();
//        light.intensity = source->getIntensity();
//        light.position = source->getPosition();
//    }
//
//    _directionalLightsSize = directionalLights.size();
//    for (int i = 0; i < directionalLights.size(); ++i) {
//        auto source = dynamic_cast<const DirectionalLightSource *>(directionalLights[i]);
//        auto &light = this->directionalLights[i];
//
//        light.color = source->getColor();
//        light.intensity = source->getIntensity();
//        light.direction = source->getDirection();
//    }
//
//    _spotlightsSize = spotlights.size();
//    for (int i = 0; i < spotlights.size(); ++i) {
//        auto source = dynamic_cast<const SpotlightSource *>(spotlights[i]);
//        auto &light = this->spotlights[i];
//
//        light.color = source->getColor();
//        light.intensity = source->getIntensity();
//        light.position = source->getPosition();
//
//        light.direction = source->getDirection();
//        light.cutOff = glm::cos(glm::radians(source->getCutOff()));
//        light.outerCutOff = glm::cos(glm::radians(source->getOuterCutOff()));
//    }
//}
