#pragma once

#include <vector>

#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape {
public:
    virtual const std::vector<glm::vec3> &getVertices() const = 0;

    virtual const std::vector<GLushort> &getIndices() const = 0;
};
