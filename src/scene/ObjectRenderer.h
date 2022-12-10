#pragma once

#include <memory>
#include <vector>
#include <unordered_set>

#include "DrawableObject.h"
#include "../model/shader/Shader.h"
#include "Camera.h"


class ObjectRenderer {
private:
    std::vector<DrawableObject *> _objects;

    Camera &_camera;

public:
    explicit ObjectRenderer(Camera &camera);

    void render();

    void addObject(DrawableObject *);

};
