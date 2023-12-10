#include "Scene.h"

#include "../window/Window.h"

size_t Scene::_objectCounter = 0;

void Scene::draw() {
    _camera->update();

    _lightManager.updateLights(false);

    for (const auto& item: _drawCallbacks) {
        item(*this);
    }

    _backgroundObjectRenderer->render();

    _window->clearDepth();

    _objectRenderer->render();
}

Scene::Scene(Window* window) : _window(window) {
    _camera = std::make_unique<Camera>(this, glm::vec3(5, 0, 5));
    _objectRenderer = std::make_unique<ObjectRenderer>(*_camera);
    _backgroundObjectRenderer = std::make_unique<ObjectRenderer>(*_camera);
}

Camera* Scene::getCamera() {
    return _camera.get();
}

void Scene::addObject(DrawableObject* object) {
    object->_id = _objectCounter++;
    this->_objectRenderer->addObject(object);
}

void Scene::addBackgroundObject(DrawableObject* object) {
    this->_backgroundObjectRenderer->addObject(object);
}

void Scene::addLightSource(LightSource* source) {
    _lightManager.addLight(source);
}

void Scene::onShow() {
    _active = true;
    _lightManager.updateLights(true);
    _active = true;
}

void Scene::onHide() {
    _active = false;
}

void Scene::addDrawCallback(const std::function<void(Scene&)>& callback) {
    this->_drawCallbacks.push_back(callback);
}

void Scene::updateLights() {
    _lightManager.updateLights(false);
    // for (auto shader: _lightShaders) {
    //     shader->use([this](Shader& shader) {
    //         auto component = shader.getComponent<LightShaderComponent>();
    //
    //         size_t lightIndex = 0;
    //         size_t directionalLightIndex = 0;
    //         size_t spotlightIndex = 0;
    //
    //         for (const auto& item: _lightSources) {
    //             auto light = item.get();
    //
    //             size_t* index;
    //
    //             if (dynamic_cast<DirectionalLightSource *>(light) != nullptr) {
    //                 index = &directionalLightIndex;
    //             } else if (dynamic_cast<SpotlightSource *>(light) != nullptr) {
    //                 index = &spotlightIndex;
    //             } else {
    //                 index = &lightIndex;
    //             }
    //
    //             light->updateShader(*index, component);
    //             (*index)++;
    //         }
    //
    //         component->lights.setSize(lightIndex);
    //         component->directionalLights.setSize(directionalLightIndex);
    //         component->spotlights.setSize(spotlightIndex);
    //     });
    // }
}

bool Scene::isActive() const {
    return _active;
}

std::optional<DrawableObject*> Scene::getObject(size_t id) const {
    return _objectRenderer->getObject(id);
}

Window* Scene::getWindow() const {
    return _window;
}
