//
// Created by Jan Bednář on 04.11.2023.
//

#ifndef CV1_LIGHTSHADERCOMPONENT_H
#define CV1_LIGHTSHADERCOMPONENT_H


#include "ShaderComponent.h"

#include "../Shader.h"

class UniformLightStruct : public Noncopyable {
public:
    UniformVariable<glm::vec3> position;
    UniformVariable<glm::vec3> color;
    UniformVariable<GLfloat> intensity;

    explicit UniformLightStruct(GLuint programId);

    UniformLightStruct(GLuint programId, const std::string &prefix);


    UniformLightStruct(UniformLightStruct &&) = default;

    UniformLightStruct &operator=(UniformLightStruct &&) = default;

    virtual ~UniformLightStruct() = default;
};

class UniformSpotlightStruct : public UniformLightStruct {
public:
    UniformVariable<glm::vec3> direction;
    UniformVariable<GLfloat> cutOff;
    UniformVariable<GLfloat> outerCutOff;

    explicit UniformSpotlightStruct(GLuint programId);

    UniformSpotlightStruct(GLuint programId, const std::string &variableName);
};

class UniformDirectionalLightStruct : public UniformLightStruct {
public:
    UniformVariable<glm::vec3> direction;

    explicit UniformDirectionalLightStruct(GLuint programId);

    UniformDirectionalLightStruct(GLuint programId, const std::string &variableName);
};

class LightShaderComponent : public ShaderComponent {
public:
    static factoryType *factory;

    UniformVariable<glm::vec3> viewPosVector;

    UniformVariableArray<UniformLightStruct> lights;
//    UniformVariable<GLuint> _lightsSize{"lightsSize", _programId};
//    std::vector<UniformLightStruct> lights;

    UniformVariableArray<UniformSpotlightStruct> spotlights;
//    UniformVariable<GLuint> _spotlightsSize{"spotlightsSize", _programId};
//    std::vector<UniformSpotlightStruct> spotlights;

    UniformVariableArray<UniformDirectionalLightStruct> directionalLights;
//    UniformVariable<GLuint> _directionalLightsSize{"directionalLightsSize", _programId};
//    std::vector<UniformDirectionalLightStruct> directionalLights;

    explicit LightShaderComponent(Shader *shader);
};


#endif //CV1_LIGHTSHADERCOMPONENT_H
