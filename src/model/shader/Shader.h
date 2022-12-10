#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>
#include <array>

#include "../../util/Usable.h"
#include "../../util/Noncopyable.h"
#include "../../scene/LightSource.h"
#include "UniformVariable.h"

#define MAX_LIGHTS 16

class UniformLightStruct : public Noncopyable {
public:
    UniformVariable<glm::vec3> position;
    UniformVariable<glm::vec3> color;
    UniformVariable<GLfloat> intensity;

    UniformLightStruct(GLuint programId, const std::string &variableName, GLuint index);

    UniformLightStruct(UniformLightStruct &&) = default;

    UniformLightStruct &operator=(UniformLightStruct &&) = default;

    virtual ~UniformLightStruct() = default;
};

class UniformSpotlightStruct : public UniformLightStruct {
public:
    UniformVariable<glm::vec3> direction;
    UniformVariable<GLfloat> cutOff;
    UniformVariable<GLfloat> outerCutOff;

    UniformSpotlightStruct(GLuint programId, const std::string &variableName, GLuint index);
};

class UniformDirectionalLightStruct : public UniformLightStruct {
public:
    UniformVariable<glm::vec3> direction;

    UniformDirectionalLightStruct(GLuint programId, const std::string &variableName, GLuint index);
};

class Shader : public Usable<Shader>, public Noncopyable {
private:
    GLuint _programId;
    GLuint _vertexId;
    GLuint _fragmentId;

    UniformVariable<GLuint> _lightsSize{"lightsSize", _programId};
    std::vector<UniformLightStruct> _lights;

    UniformVariable<GLuint> _spotlightsSize{"spotlightsSize", _programId};
    std::vector<UniformSpotlightStruct> _spotlights;

    UniformVariable<GLuint> _directionalLightsSize{"directionalLightsSize", _programId};
    std::vector<UniformDirectionalLightStruct> _directionalLights;

    Shader(GLuint programId, GLuint vertexId, GLuint fragmentId);

    friend class ShaderLoader;

public:
    UniformVariable<glm::mat4> modelMatrix{"modelMatrix", _programId};
    UniformVariable<glm::mat4> viewMatrix{"viewMatrix", _programId};
    UniformVariable<glm::mat4> projectionMatrix{"projectionMatrix", _programId};

    UniformVariable<glm::vec3> viewPosVector{"viewPos", _programId};

    UniformVariable<GLboolean> hasTexture{"hasTexture", _programId};
    UniformVariable<GLint> textureUnitID{"textureUnitID", _programId};

    ~Shader() override;

    void setLightArray(const std::vector<LightSource *> &lightSources);

private:
    void startUsing() override;

    void stopUsing() override;
};
