#include "LightSource.h"

LightSource::LightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity) : _position(position),
                                                                                               _color(color),
                                                                                               _intensity(intensity) {}

const glm::vec3 &LightSource::getPosition() const {
    return _position;
}

const glm::vec3 &LightSource::getColor() const {
    return _color;
}

float LightSource::getIntensity() const {
    return _intensity;
}
