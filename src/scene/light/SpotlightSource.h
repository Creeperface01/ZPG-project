#pragma once

#include "LightSource.h"

#include "glm/vec3.hpp"

class SpotlightSource : public LightSource {
private:
    glm::vec3 _direction;
    float _cutOff;
    float _outerCutOff;

public:
    SpotlightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity, const glm::vec3 &direction,
                    float cutOff, float outerCutOff);

    void updateShader(size_t index, LightShaderComponent *component) const override;

    [[nodiscard]] const glm::vec3 &getDirection() const;

    [[nodiscard]] float getCutOff() const;

    [[nodiscard]] float getOuterCutOff() const;

    void setDirection(const glm::vec3 &direction);

    void setCutOff(float cutOff);

    void setOuterCutOff(float outerCutOff);
};
