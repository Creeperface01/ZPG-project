

#include "RotationObjectComponent.h"

RotationObjectComponent::RotationObjectComponent(float angle): _angle(angle) {
}

float RotationObjectComponent::getAngle() const {
    return _angle;
}

void RotationObjectComponent::setAngle(float angle) {
    _angle = angle;
}
