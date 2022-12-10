#pragma once

#include "BaseTransform.h"

#include <glm/vec3.hpp>

class RotateTransform : public BaseTransform {
private:
    glm::vec3 _axis;

    glm::vec3 _center;

    float _angle;

public:
    RotateTransform(const glm::vec3 &axis, const glm::vec3 &center, float angle);

    glm::mat4 transform(const glm::mat4 &modelMatrix) override;
};
