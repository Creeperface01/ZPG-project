//
// Created by Jan Bednář on 04.11.2023.
//

#include "LightShaderComponent.h"

#include <string>

ShaderComponent::factoryType *LightShaderComponent::factory = ShaderComponent::baseFactory<LightShaderComponent>();

LightShaderComponent::LightShaderComponent(Shader *shader) : ShaderComponent(shader),
                                                             viewPosVector(
                                                                     shader->makeVariable<glm::vec3>(
                                                                             "viewPos"
                                                                     )
                                                             ),

                                                             lights(
                                                                     shader
                                                                             ->makeArrayVariable<UniformLightStruct>(
                                                                                     "lights",
                                                                                     "lightsSize",
                                                                                     32
                                                                             )
                                                             ),
                                                             spotlights(
                                                                     shader
                                                                             ->makeArrayVariable<UniformSpotlightStruct>(
                                                                                     "spotlights",
                                                                                     "spotlightsSize",
                                                                                     32
                                                                             )
                                                             ),
                                                             directionalLights(
                                                                     shader
                                                                             ->makeArrayVariable<UniformDirectionalLightStruct>(
                                                                                     "directionalLights",
                                                                                     "directionalLightsSize",
                                                                                     32
                                                                             )
                                                             ) {
}

UniformLightStruct::UniformLightStruct(GLuint programId) :
        position{"position", programId},
        color{"color", programId},
        intensity{"intensity", programId} {
}

UniformLightStruct::UniformLightStruct(GLuint programId, const std::string &prefix) :
        position{prefix, "position", programId},
        color{prefix, "color", programId},
        intensity{prefix, "intensity", programId} {
}

UniformSpotlightStruct::UniformSpotlightStruct(GLuint programId)
        : UniformLightStruct(programId),
          direction{"direction", programId},
          cutOff{"cutOff", programId},
          outerCutOff{"outerCutOff", programId} {}

UniformSpotlightStruct::UniformSpotlightStruct(GLuint programId, const std::string &prefix)
        : UniformLightStruct(programId, prefix),
          direction{prefix, "direction", programId},
          cutOff{prefix, "cutOff", programId},
          outerCutOff{prefix, "outerCutOff", programId} {}

UniformDirectionalLightStruct::UniformDirectionalLightStruct(
        GLuint programId
) : UniformLightStruct(programId),
    direction{"direction", programId} {
}

UniformDirectionalLightStruct::UniformDirectionalLightStruct(
        GLuint programId,
        const std::string &prefix
) : UniformLightStruct(programId, prefix),
    direction{prefix, "direction", programId} {

}
