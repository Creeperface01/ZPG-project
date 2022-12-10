#include "Scene.h"

#include "../window/Window.h"

void Scene::draw() {
    _camera->update();

    for (const auto &item: _drawCallbacks) {
        item(*this);
    }

    _backgroundObjectRenderer->render();

    _window->clearDepth();

    _objectRenderer->render();
}

Scene::Scene(Window *window) : _window(window) {
    _camera = std::make_unique<Camera>(*window, glm::vec3(5, 0, 5));
    _objectRenderer = std::make_unique<ObjectRenderer>(*_camera);
    _backgroundObjectRenderer = std::make_unique<ObjectRenderer>(*_camera);
}

Camera *Scene::getCamera() {
    return _camera.get();
}

void Scene::addObject(DrawableObject *object) {
    this->_objectRenderer->addObject(object);
}

void Scene::addBackgroundObject(DrawableObject *object) {
    this->_backgroundObjectRenderer->addObject(object);
}

void Scene::addLightSource(LightSource *source) {
    this->_lightSources.push_back(std::unique_ptr<LightSource>(source));
}

void Scene::onShow() {
    updateLights();
}

void Scene::onHide() {

}

void Scene::addDrawCallback(const std::function<void(Scene &)> &callback) {
    this->_drawCallbacks.push_back(callback);
}

void Scene::updateLights() {
    std::vector<LightSource *> sources;
    sources.reserve(this->_lightSources.size());

    std::transform(
            this->_lightSources.begin(),
            this->_lightSources.end(),
            std::back_inserter(sources),
            [](auto &source) { return source.get(); }
    );

    for (auto &shader: ShaderRegistry::get()->getAll()) {
        shader->use([&sources](Shader &shader) {
            shader.setLightArray(sources);
        });
    }
}
