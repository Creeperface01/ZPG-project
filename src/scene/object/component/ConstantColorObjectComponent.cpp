#include "ConstantColorObjectComponent.h"
#include "../../../model/shader/component/ConstantColorShaderComponent.h"

void ConstantColorObjectComponent::beforeDraw(DrawableObject *object) {
    auto shader = object->getShader();

    auto constantColorComponent = shader->getComponentIfExists<ConstantColorShaderComponent>();

    if(!constantColorComponent.has_value()) {
        return;
    }

    constantColorComponent.value()->color = _color;
}

ConstantColorObjectComponent::ConstantColorObjectComponent(glm::vec3 color) : _color(color) {

}
