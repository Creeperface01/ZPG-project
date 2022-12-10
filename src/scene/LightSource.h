#pragma once

#include <glm/vec3.hpp>

class LightSource {
private:
    glm::vec3 _position;
    glm::vec3 _color;
    float _intensity;

public:
    LightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity);

    virtual ~LightSource() = default;

    [[nodiscard]] const glm::vec3 &getPosition() const;

    [[nodiscard]] const glm::vec3 &getColor() const;

    [[nodiscard]] float getIntensity() const;
};
