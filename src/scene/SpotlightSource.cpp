#include "SpotlightSource.h"

SpotlightSource::SpotlightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity,
                                 const glm::vec3 &direction, float cutOff, float outerCutOff) : LightSource(position,
                                                                                                            color,
                                                                                                            intensity),
                                                                                                _direction(direction),
                                                                                                _cutOff(cutOff),
                                                                                                _outerCutOff(
                                                                                                        outerCutOff) {}

const glm::vec3 &SpotlightSource::getDirection() const {
    return _direction;
}

float SpotlightSource::getCutOff() const {
    return _cutOff;
}

float SpotlightSource::getOuterCutOff() const {
    return _outerCutOff;
}

void SpotlightSource::setDirection(const glm::vec3 &direction) {
    _direction = direction;
}

void SpotlightSource::setCutOff(float cutOff) {
    _cutOff = cutOff;
}

void SpotlightSource::setOuterCutOff(float outerCutOff) {
    _outerCutOff = outerCutOff;
}
