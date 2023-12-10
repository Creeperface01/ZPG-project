#include "DirectionalLightSource.h"

DirectionalLightSource::DirectionalLightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity,
                                               const glm::vec3 &direction) : LightSource(position, color, intensity),
                                                                             _direction(direction) {}

const glm::vec3 &DirectionalLightSource::getDirection() const {
    return _direction;
}

void DirectionalLightSource::updateShader(size_t index, LightShaderComponent *component) const {
    auto &light = component->directionalLights[index];
    light.position = _position;
    light.color = _color;
    light.intensity = _intensity;
    light.direction = _direction;
}
