#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "../scene/Camera.h"
#include "../scene/ObjectRenderer.h"
#include "DrawableObject.h"
#include "LightSource.h"

class Window;

class Scene {
private:
    Window *_window;

    std::unique_ptr<Camera> _camera;
    std::unique_ptr<ObjectRenderer> _backgroundObjectRenderer;
    std::unique_ptr<ObjectRenderer> _objectRenderer;

    std::vector<std::unique_ptr<LightSource>> _lightSources;

    std::vector<std::function<void(Scene &)>> _drawCallbacks;

public:
    explicit Scene(Window *window);

    void draw();

    Camera *getCamera();

    void addObject(DrawableObject *object);

    void addBackgroundObject(DrawableObject *object);

    void addLightSource(LightSource *source);

    void updateLights();

    void onShow();

    void onHide();

    void addDrawCallback(const std::function<void(Scene &)> &callback);

};
