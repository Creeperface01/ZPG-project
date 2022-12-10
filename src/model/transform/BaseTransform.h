#pragma once

#include <glm/mat4x4.hpp>

class BaseTransform {
public:
    virtual glm::mat4 transform(const glm::mat4 &modelMatrix) = 0;
};
