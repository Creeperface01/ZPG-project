#pragma once

#include "LightSource.h"

class DirectionalLightSource : public LightSource {
private:
    glm::vec3 _direction;

public:
    DirectionalLightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity,
                           const glm::vec3 &direction);

    const glm::vec3 &getDirection() const;
};
