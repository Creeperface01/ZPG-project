#pragma once

#include "BaseTransform.h"

#include <glm/vec3.hpp>

class ScaleTransform : public BaseTransform {
private:
    glm::vec3 _scale;
public:
    explicit ScaleTransform(const glm::vec3 &scale);

    glm::mat4 transform(const glm::mat4 &modelMatrix) const override;

    glm::vec3 getScale() const;
};
