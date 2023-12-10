#include "ObjectRenderer.h"
#include "../model/shader/component/LightShaderComponent.h"

void ObjectRenderer::render() {
    _camera.recalculateMatrices();

    auto& vp = _camera.getEye();

    auto& vm = _camera.getViewMatrix();
    auto& pm = _camera.getProjectionMatrix();

    for (auto& item: ShaderRegistry::get()->getAll()) {
        //TODO: filter used shaders
        item->use([&vp, &vm, &pm](Shader& shader) {
            auto lightComponent = shader.getComponentIfExists<LightShaderComponent>();

            if (lightComponent.has_value()) {
                lightComponent.value()->viewPosVector = vp;
            }

            shader.viewMatrix = vm;
            shader.projectionMatrix = pm;
        });
    }

    for (const auto& [id, obj]: _objects) {
        debugGlCall(glStencilFunc, GL_ALWAYS, obj->getId(), 0xff);
        obj->draw();
    }
}

void ObjectRenderer::addObject(DrawableObject* obj) {
    this->_objects.insert({obj->getId(), obj});
}

std::optional<DrawableObject *> ObjectRenderer::getObject(size_t id) const {
    auto it = _objects.find(id);

    if (it == _objects.end()) {
        return std::nullopt;
    }

    return {it->second};
}

ObjectRenderer::ObjectRenderer(Camera& camera) : _camera(camera) {
}
