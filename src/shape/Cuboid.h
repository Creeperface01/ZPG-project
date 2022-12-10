#pragma once


#include "Shape.h"

class Cuboid : public Shape {
private:
    glm::vec3 _min;
    glm::vec3 _max;

    std::vector<glm::vec3> vertices;

    std::vector<GLushort> indices;

public:
    Cuboid(const glm::vec3 &p1, const glm::vec3 &p2);

    Cuboid(float x1, float y1, float z1, float x2, float y2, float z2);

    [[nodiscard]] const std::vector<glm::vec3> &getVertices() const override;

    [[nodiscard]] const std::vector<GLushort> &getIndices() const override;

};
