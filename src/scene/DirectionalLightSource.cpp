#include "DirectionalLightSource.h"

DirectionalLightSource::DirectionalLightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity,
                                               const glm::vec3 &direction) : LightSource(position, color, intensity),
                                                                             _direction(direction) {}

const glm::vec3 &DirectionalLightSource::getDirection() const {
    return _direction;
}
