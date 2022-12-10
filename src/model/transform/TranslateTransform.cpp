#include "TranslateTransform.h"

#include <glm/gtc/matrix_transform.hpp>

TranslateTransform::TranslateTransform(const glm::vec3 &position) : _position(position) {}

glm::mat4 TranslateTransform::transform(const glm::mat4 &modelMatrix) {
    return glm::translate(modelMatrix, this->_position);
}
