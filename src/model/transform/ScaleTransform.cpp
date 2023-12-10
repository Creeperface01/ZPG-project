#include "ScaleTransform.h"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 ScaleTransform::transform(const glm::mat4 &modelMatrix) const {
    return glm::scale(modelMatrix, this->_scale);
}

glm::vec3 ScaleTransform::getScale() const {
    return _scale;
}

ScaleTransform::ScaleTransform(const glm::vec3 &scale) : _scale(scale) {}
