#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <optional>

#include "../scene/Camera.h"
#include "../scene/ObjectRenderer.h"
#include "light/DirectionalLightSource.h"
#include "light/LightManager.h"
#include "object/DrawableObject.h"
#include "light/LightSource.h"
#include "light/SpotlightSource.h"

class Window;

class Scene {
private:
    static size_t _objectCounter;

    Window *_window;

    bool _active = false;

    std::unique_ptr<Camera> _camera;
    std::unique_ptr<ObjectRenderer> _backgroundObjectRenderer;
    std::unique_ptr<ObjectRenderer> _objectRenderer;

    std::vector<std::function<void(Scene &)>> _drawCallbacks;

    LightManager _lightManager;

public:
    explicit Scene(Window *window);

    Window *getWindow() const;

    void draw();

    Camera *getCamera();

    void addObject(DrawableObject *object);

    void addBackgroundObject(DrawableObject *object);

    void addLightSource(LightSource *source);

    void updateLights();

    void onShow();

    void onHide();

    void addDrawCallback(const std::function<void(Scene &)> &callback);

    bool isActive() const;

    std::optional<DrawableObject *> getObject(size_t id) const;
};
