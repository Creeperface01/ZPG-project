#include "LightSource.h"

LightSource::LightSource(const glm::vec3& position, const glm::vec3& color, float intensity) : _position(position),
    _color(color),
    _intensity(intensity) {
}

const glm::vec3& LightSource::getPosition() const {
    return _position;
}

const glm::vec3& LightSource::getColor() const {
    return _color;
}

float LightSource::getIntensity() const {
    return _intensity;
}

bool LightSource::isDirty() const {
    return _dirty;
}

void LightSource::setPosition(const glm::vec3& position) {
    _position = position;
    setDirty(true);
}

void LightSource::setColor(const glm::vec3& color) {
    _color = color;
    setDirty(true);
}

void LightSource::setIntensity(float intensity) {
    _intensity = intensity;
    setDirty(true);
}

void LightSource::setDirty(bool dirty) {
    _dirty = true;
}

void LightSource::updateShader(size_t index, LightShaderComponent* component) const {
    auto& light = component->lights[index];
    light.position = _position;
    light.color = _color;
    light.intensity = _intensity;
}

void LightSource::updateShaders(size_t index, const std::vector<LightShaderComponent *> &components) const {
    for (const auto component: components) {
        updateShader(index, component);
    }
}
