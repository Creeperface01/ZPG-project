#pragma once

#include "BaseTransform.h"

#include <glm/vec3.hpp>

class TranslateTransform : public BaseTransform {
private:
    glm::vec3 _position;

public:
    explicit TranslateTransform(const glm::vec3 &position);

    glm::mat4 transform(const glm::mat4 &modelMatrix) override;
};
