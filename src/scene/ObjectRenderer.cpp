#include "ObjectRenderer.h"

void ObjectRenderer::render() {
    _camera.recalculateMatrices();

    auto &vp = _camera.getEye();

    auto &vm = _camera.getViewMatrix();
    auto &pm = _camera.getProjectionMatrix();

    for (auto &item: ShaderRegistry::get()->getAll()) { //TODO: filter used shaders
        item->use([&vp, &vm, &pm](Shader &shader) {
            shader.viewPosVector = vp;

            shader.viewMatrix = vm;
            shader.projectionMatrix = pm;
        });
    }

    for (const auto &obj: _objects) {
        obj->draw();
    }
}

void ObjectRenderer::addObject(DrawableObject *obj) {
    this->_objects.push_back(obj);
}

ObjectRenderer::ObjectRenderer(Camera &camera) : _camera(camera) {
}
