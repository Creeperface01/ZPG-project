#pragma once

#include <optional>

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../../model/BaseModel.h"
#include "../../model/transform/RotateTransform.h"
#include "../../model/transform/TranslateTransform.h"
#include "../../model/transform/ScaleTransform.h"
#include "../../util/ObservableValue.h"
#include "component/ObjectComponent.h"

class DrawableObject {
private:
    size_t _id;

    BaseModel *_model;

    Shader *_shader;

    std::optional<glm::mat4> _modelMatrix;

    std::optional<ScaleTransform> _scaleTransform;

    std::optional<TranslateTransform> _translateTransform;

    std::optional<RotateTransform> _rotateTransform;

    std::vector<std::unique_ptr<ObjectComponent>> _components;

    glm::mat4 calculateModelMatrix() const;

    void resetModelMatrix();

    void refreshModelMatrix();
public:
    friend class Scene;

    DrawableObject(BaseModel *model, Shader *shader);

    DrawableObject(BaseModel *model, Shader *shader, const std::vector<ObjectComponent *> &components);

    void draw();

    size_t getId() const;

    void setTranslation(const glm::vec3 &position);

    glm::vec3 getTranslation() const;

    void setRotation(const glm::vec3 &axis, float angle);

    void setRotation(const glm::vec3 &axis, float radius, float angle);

    void setPositionAndRotation(
            const glm::vec3 &position,
            float angle,
            const glm::vec3 &center,
            const glm::vec3 &axis
    );

    void setScale(const glm::vec3 &scale);

    void setScale(float scale);

    glm::vec3 getFinalPosition() const;

    BaseModel *getModel() const;

    Shader *getShader() const;

    glm::mat4 getModelMatrix();

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
            throw std::runtime_error("Object component not found for type " + std::string(typeid(T).name()));
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
};
