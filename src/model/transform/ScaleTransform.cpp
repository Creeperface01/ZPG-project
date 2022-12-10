#include "ScaleTransform.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 ScaleTransform::transform(const glm::mat4 &modelMatrix) {
    return glm::scale(modelMatrix, this->_scale);
}

ScaleTransform::ScaleTransform(const glm::vec3 &scale) : _scale(scale) {}
