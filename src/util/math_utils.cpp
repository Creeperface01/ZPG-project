#include "math_utils.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 math_utils::rotate(const glm::vec3& axis, float radius, float angle) {
    return rotate(glm::zero<glm::vec3>(), axis, radius, angle);
}

glm::vec3 math_utils::rotate(const glm::vec3& base, const glm::vec3& axis, float radius, float angle) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    glm::vec3 rotated = rotationMatrix * glm::vec4(radius, 0, 0, 1);

    return base + rotated;
}

std::function<glm::vec3(float t)> math_utils::createBezierSplineGenerator(const glm::vec3& p0, const glm::vec3& p1,
    const glm::vec3& p2, const glm::vec3& p3) {
    glm::mat4 bezierMatrix(
        -1, 3, -3, 1,
        3, -6, 3, 0,
        -3, 3, 0, 0,
        1, 0, 0, 0
    );

    glm::mat4 controlPointsMatrix(
        p0.x, p1.x, p2.x, p3.x,
        p0.y, p1.y, p2.y, p3.y,
        p0.z, p1.z, p2.z, p3.z,
        1, 1, 1, 1
    );

    return [bezierMatrix, controlPointsMatrix](float t) {
        glm::vec4 parameterVector(t * t * t, t * t, t, 1);

        return controlPointsMatrix * bezierMatrix * parameterVector;
    };
}
