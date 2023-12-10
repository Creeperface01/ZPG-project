#pragma once

#include <glm/mat4x4.hpp>
#include "../../util/Observable.h"

class BaseTransform {
public:
    virtual glm::mat4 transform(const glm::mat4 &modelMatrix) const = 0;
};
