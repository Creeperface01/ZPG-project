#include "RotateTransform.h"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

RotateTransform::RotateTransform(
        const glm::vec3 &axis,
        const glm::vec3 &center,
        float radius,
        float angle
) : _axis(axis), _center(center), _radius(radius), _angle(angle) {}

glm::mat4 RotateTransform::transform(const glm::mat4 &modelMatrix) const {
//    if (_center == glm::zero<glm::vec3>()) {
//        return glm::rotate(modelMatrix, this->_angle, this->_axis);
//    }

    auto result = modelMatrix;

    auto center = _center;
//    center -= glm::vec3(_radius, _radius, _radius);

    result = glm::translate(result, center);
    result = glm::rotate(result, _angle, _axis);
    result = glm::translate(result, -center);

    return result;
}
