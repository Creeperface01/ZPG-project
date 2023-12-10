#pragma once

#include <unordered_map>
#include <optional>

#include "object/DrawableObject.h"
#include "Camera.h"


class ObjectRenderer {
private:
    std::unordered_map<size_t, DrawableObject *> _objects;

    Camera &_camera;

public:
    explicit ObjectRenderer(Camera &camera);

    void render();

    void addObject(DrawableObject *);

    std::optional<DrawableObject*> getObject(size_t id) const;
};
