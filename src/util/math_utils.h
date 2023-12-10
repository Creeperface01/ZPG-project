#ifndef MATH_H
#define MATH_H

#include <functional>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace math_utils {
    glm::vec3 rotate(const glm::vec3& axis, float radius, float angle);

    glm::vec3 rotate(const glm::vec3& base, const glm::vec3& axis, float radius, float angle);

    std::function<glm::vec3(float t)> createBezierSplineGenerator(
        const glm::vec3& p0,
        const glm::vec3& p1,
        const glm::vec3& p2,
        const glm::vec3& p3
    );
}

#endif //MATH_H
