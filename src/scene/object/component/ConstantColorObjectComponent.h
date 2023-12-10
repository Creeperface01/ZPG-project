#ifndef CV1_CONSTANTCOLOROBJECTCOMPONENT_H
#define CV1_CONSTANTCOLOROBJECTCOMPONENT_H


#include "ObjectComponent.h"

#include "../DrawableObject.h"

#include <glm/vec3.hpp>

class ConstantColorObjectComponent : public ObjectComponent {
private:
    glm::vec3 _color;
public:
    explicit ConstantColorObjectComponent(glm::vec3 color);

    void beforeDraw(DrawableObject *object) override;
};


#endif //CV1_CONSTANTCOLOROBJECTCOMPONENT_H
