#include "Shader.h"

#include "../../util/debug.h"
#include "../../scene/SpotlightSource.h"
#include "../../scene/DirectionalLightSource.h"

#include <glm/gtc/matrix_transform.hpp>

Shader::Shader(
        GLuint programId,
        GLuint vertexId,
        GLuint fragmentId
) : _programId(programId),
    _vertexId(vertexId),
    _fragmentId(fragmentId) {

    for (int i = 0; i < MAX_LIGHTS; ++i) {
        _lights.emplace_back(_programId, "lights", i);
        _spotlights.emplace_back(_programId, "spotlights", i);
        _directionalLights.emplace_back(_programId, "directionalLights", i);
    }

//    _lights.reserve(MAX_LIGHTS);
//    _spotlights.reserve(MAX_LIGHTS);
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

void Shader::setLightArray(const std::vector<LightSource *> &lightSources) {
    assert(lightSources.size() <= MAX_LIGHTS && "Max light sources count exceeded");

    std::vector<const LightSource *> lights;
    std::vector<const LightSource *> directionalLights;
    std::vector<const LightSource *> spotlights;

    std::copy_if(
            lightSources.begin(),
            lightSources.end(),
            std::back_inserter(lights),
            [](const LightSource *source) {
                return !dynamic_cast<const SpotlightSource *>(source)
                       && !dynamic_cast<const DirectionalLightSource *>(source);
            }
    );

    std::copy_if(
            lightSources.begin(),
            lightSources.end(),
            std::back_inserter(directionalLights),
            [](const LightSource *source) { return dynamic_cast<const DirectionalLightSource *>(source); }
    );

    std::copy_if(
            lightSources.begin(),
            lightSources.end(),
            std::back_inserter(spotlights),
            [](const LightSource *source) { return dynamic_cast<const SpotlightSource *>(source); }
    );

    _lightsSize = lights.size();
    for (int i = 0; i < lights.size(); ++i) {
        auto source = lights[i];
        auto &light = this->_lights[i];

        light.color = source->getColor();
        light.intensity = source->getIntensity();
        light.position = source->getPosition();
    }

    _directionalLightsSize = directionalLights.size();
    for (int i = 0; i < directionalLights.size(); ++i) {
        auto source = dynamic_cast<const DirectionalLightSource *>(directionalLights[i]);
        auto &light = this->_directionalLights[i];

        light.color = source->getColor();
        light.intensity = source->getIntensity();
        light.direction = source->getDirection();
    }

    _spotlightsSize = spotlights.size();
    for (int i = 0; i < spotlights.size(); ++i) {
        auto source = dynamic_cast<const SpotlightSource *>(spotlights[i]);
        auto &light = this->_spotlights[i];

        light.color = source->getColor();
        light.intensity = source->getIntensity();
        light.position = source->getPosition();

        light.direction = source->getDirection();
        light.cutOff = glm::cos(glm::radians(source->getCutOff()));
        light.outerCutOff = glm::cos(glm::radians(source->getOuterCutOff()));
    }
}

UniformLightStruct::UniformLightStruct(GLuint programId, const std::string &variableName, GLuint index) :
        position{variableName + "[" + std::to_string(index) + "].position", programId},
        color{variableName + "[" + std::to_string(index) + "].color", programId},
        intensity{variableName + "[" + std::to_string(index) + "].intensity", programId} {

}

UniformSpotlightStruct::UniformSpotlightStruct(GLuint programId, const std::string &variableName, GLuint index)
        : UniformLightStruct(programId, variableName, index),
          direction{variableName + "[" + std::to_string(index) + "].direction", programId},
          cutOff{variableName + "[" + std::to_string(index) + "].cutOff", programId},
          outerCutOff{variableName + "[" + std::to_string(index) + "].outerCutOff", programId} {}

UniformDirectionalLightStruct::UniformDirectionalLightStruct(
        GLuint programId,
        const std::string &variableName,
        GLuint index
) : UniformLightStruct(programId, variableName, index),
    direction{variableName + "[" + std::to_string(index) + "].direction", programId} {

}
