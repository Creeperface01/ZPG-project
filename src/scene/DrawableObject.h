#pragma once

#include <optional>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../model/BaseModel.h"
#include "../model/transform/RotateTransform.h"
#include "../model/transform/TranslateTransform.h"
#include "../model/transform/ScaleTransform.h"

class DrawableObject {
private:
    BaseModel *_model;

//    glm::mat4 _modelMatrix = glm::mat4(1.0f);

    std::optional<ScaleTransform> _scaleTransform;

    std::optional<TranslateTransform> _translateTransform;

    std::optional<RotateTransform> _rotateTransform;

public:
    explicit DrawableObject(BaseModel *model);

    void draw();

    void setPosition(const glm::vec3 &position);

    void setRotation(const glm::vec3 &axis, float angle);

    void setRotation(const glm::vec3 &axis, const glm::vec3 &center, float angle);

    void setPositionAndRotation(
            const glm::vec3 &position,
            float angle,
            const glm::vec3 &center,
            const glm::vec3 &axis
    );

    void setScale(const glm::vec3 &scale);
};
