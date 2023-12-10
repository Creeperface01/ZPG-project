#include "ModelObjectComponent.h"

#include "../DrawableObject.h"

void ModelObjectComponent::init(DrawableObject *object) {
    auto componentOptional = object->getShader()->getComponentIfExists<ModelShaderComponent>();
    _shaderComponent = componentOptional.value_or(nullptr);
}

void ModelObjectComponent::beforeDraw(DrawableObject *object) {
    if(_shaderComponent == nullptr) {
        return;
    }

    _shaderComponent->modelMatrix = object->getModelMatrix();
}
