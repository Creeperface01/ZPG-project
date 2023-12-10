

#ifndef CV1_MODELOBJECTCOMPONENT_H
#define CV1_MODELOBJECTCOMPONENT_H


#include "ObjectComponent.h"
#include "../../../model/shader/component/ModelShaderComponent.h"

class ModelObjectComponent : public ObjectComponent {
private:
    ModelShaderComponent *_shaderComponent = nullptr;
public:
    void init(DrawableObject *object) override;

    void beforeDraw(DrawableObject *object) override;
};


#endif //CV1_MODELOBJECTCOMPONENT_H
