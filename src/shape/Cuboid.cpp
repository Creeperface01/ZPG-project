#include "Cuboid.h"

#include <glm/vec2.hpp>
#include <algorithm>
#include <tuple>

Cuboid::Cuboid(const glm::vec3 &p1, const glm::vec3 &p2) {
    _min = glm::vec3(
            std::min(p1.x, p2.x),
            std::min(p1.y, p2.y),
            std::min(p1.z, p2.z)
    );

    _max = glm::vec3(
            std::max(p1.x, p2.x),
            std::max(p1.y, p2.y),
            std::max(p1.z, p2.z)
    );

    //bottom
    vertices.emplace_back(_min.x, _min.y, _min.z); // 0 - front left
    vertices.emplace_back(_max.x, _min.y, _min.z); // 1 - front right
    vertices.emplace_back(_min.x, _min.y, _max.z); // 2 - back left
    vertices.emplace_back(_max.x, _min.y, _max.z); // 3 - back right

    //top
    vertices.emplace_back(_min.x, _max.y, _min.z); // 4 - front left
    vertices.emplace_back(_max.x, _max.y, _min.z); // 5 - front right
    vertices.emplace_back(_min.x, _max.y, _max.z); // 6 - back left
    vertices.emplace_back(_max.x, _max.y, _max.z); // 7 - back right

    // right
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(5);

    indices.push_back(3);
    indices.push_back(7);
    indices.push_back(5);

    // left
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(4);

    indices.push_back(2);
    indices.push_back(6);
    indices.push_back(4);

    // back
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(7);

    indices.push_back(2);
    indices.push_back(6);
    indices.push_back(7);

    // front
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(5);

    indices.push_back(0);
    indices.push_back(4);
    indices.push_back(5);

    // up
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(7);

    indices.push_back(4);
    indices.push_back(6);
    indices.push_back(7);

    // bottom
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(3);

    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);
}

Cuboid::Cuboid(float x1, float y1, float z1, float x2, float y2, float z2)
        : Cuboid(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2)) {

}

const std::vector<glm::vec3> &Cuboid::getVertices() const {
    return vertices;
}

const std::vector<GLushort> &Cuboid::getIndices() const {
    return indices;
}
