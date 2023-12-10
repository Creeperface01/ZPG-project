#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include <string>
#include <array>
#include <typeinfo>
#include <optional>

#include "component/ShaderComponent.h"
#include "../../util/Usable.h"
#include "../../util/Noncopyable.h"
#include "UniformVariable.h"
#include "../../util/concepts.h"
#include "../../util/constructor.h"

//#define MAX_LIGHTS 16

//class UniformLightStruct : public Noncopyable {
//public:
//    UniformVariable<glm::vec3> position;
//    UniformVariable<glm::vec3> color;
//    UniformVariable<GLfloat> intensity;
//
//    UniformLightStruct(GLuint programId, const std::string &variableName, GLuint index);
//
//    UniformLightStruct(UniformLightStruct &&) = default;
//
//    UniformLightStruct &operator=(UniformLightStruct &&) = default;
//
//    virtual ~UniformLightStruct() = default;
//};
//
//class UniformSpotlightStruct : public UniformLightStruct {
//public:
//    UniformVariable<glm::vec3> direction;
//    UniformVariable<GLfloat> cutOff;
//    UniformVariable<GLfloat> outerCutOff;
//
//    UniformSpotlightStruct(GLuint programId, const std::string &variableName, GLuint index);
//};
//
//class UniformDirectionalLightStruct : public UniformLightStruct {
//public:
//    UniformVariable<glm::vec3> direction;
//
//    UniformDirectionalLightStruct(GLuint programId, const std::string &variableName, GLuint index);
//};

class Shader : public Usable<Shader>, public Noncopyable {
public:
    using shader_component_constructor = decltype(construct_with<ShaderComponent, Shader *>);
private:
    GLuint _programId;
    GLuint _vertexId;
    GLuint _fragmentId;

    std::vector<std::unique_ptr<ShaderComponent>> _components;

//    UniformVariable<GLuint> _lightsSize{"lightsSize", _programId};
//    std::vector<UniformLightStruct> lights;
//
//    UniformVariable<GLuint> _spotlightsSize{"spotlightsSize", _programId};
//    std::vector<UniformSpotlightStruct> spotlights;
//
//    UniformVariable<GLuint> _directionalLightsSize{"directionalLightsSize", _programId};
//    std::vector<UniformDirectionalLightStruct> directionalLights;

    Shader(GLuint programId, GLuint vertexId, GLuint fragmentId);

    Shader(
            GLuint programId,
            GLuint vertexId,
            GLuint fragmentId,
            const std::vector<shader_component_constructor *> &componentFactories
    );

    friend class ShaderRegistry;

public:
//    UniformVariable<glm::mat4> modelMatrix{"modelMatrix", _programId};
    UniformVariable<glm::mat4> viewMatrix{"viewMatrix", _programId};
    UniformVariable<glm::mat4> projectionMatrix{"projectionMatrix", _programId};

//    UniformVariable<bool> _hasSolidColor{"hasSolidColor", _programId};
//    UniformVariable<glm::vec3> _solidColor{"solidColor", _programId};

    ~Shader() override;

//    void setLightArray(const std::vector<LightSource *> &lightSources);

    template<typename T>
    UniformVariable<T> makeVariable(const std::string &name) const {
        return {name, _programId};
    }

    template<typename T>
    UniformVariableArray<T> makeArrayVariable(
            const std::string &prefix,
            const std::string &name,
            const std::string &lengthVariableName,
            size_t maxArraySize
    ) const {
        return {_programId, prefix + ".", name, lengthVariableName, maxArraySize};
    }

    template<typename T>
    UniformVariableArray<T> makeArrayVariable(
            const std::string &name,
            const std::string &lengthVariableName,
            size_t maxArraySize
    ) const {
        return {_programId, "", name, lengthVariableName, maxArraySize};
    }

    template<class T>
    std::optional<T*> getComponentIfExists() {
        auto it = std::find_if(
                _components.begin(),
                _components.end(),
                [](const auto &component) {
                    return dynamic_cast<T *>(component.get()) != nullptr;
                }
        );

        if (it == _components.end()) {
            return std::nullopt;
        }

        return dynamic_cast<T *>(it->get());
    }

    template<class T>
    T *getComponent() {
        std::optional<T*> component = getComponentIfExists<T>();

        if (!component.has_value()) {
            throw std::runtime_error("Shader component not found for type " + std::string(typeid(T).name()));
        }

        return component.value();
    }

    template<class T>
    bool hasComponent() {
        auto it = std::find_if(
                _components.begin(),
                _components.end(),
                [](const auto &component) {
                    return dynamic_cast<T *>(component.get()) != nullptr;
                }
        );

        return it != _components.end();
    }

private:
    void startUsing() override;

    void stopUsing() override;
};
