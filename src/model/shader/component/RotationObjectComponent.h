

#ifndef ROTATIONOBJECTCOMPONENT_H
#define ROTATIONOBJECTCOMPONENT_H
#include "../../../scene/object/component/ObjectComponent.h"


class RotationObjectComponent : public ObjectComponent {
private:
    float _angle;
public:
    explicit RotationObjectComponent(float angle);

    float getAngle() const;

    void setAngle(float angle);
};



#endif //ROTATIONOBJECTCOMPONENT_H
