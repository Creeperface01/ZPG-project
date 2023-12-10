#pragma once

#include "glm/vec3.hpp"
#include "../../model/shader/component/LightShaderComponent.h"

#include <vector>

class LightSource {
protected:
    glm::vec3 _position;
    glm::vec3 _color;
    float _intensity;

    bool _dirty = true;

public:
    LightSource(const glm::vec3 &position, const glm::vec3 &color, float intensity);

    virtual ~LightSource() = default;

    virtual void updateShader(size_t index, LightShaderComponent *component) const;

    void updateShaders(size_t index, const std::vector<LightShaderComponent *> &components) const;

    [[nodiscard]] const glm::vec3 &getPosition() const;

    [[nodiscard]] const glm::vec3 &getColor() const;

    [[nodiscard]] float getIntensity() const;

    [[nodiscard]] bool isDirty() const;

    void setPosition(const glm::vec3& position);

    void setColor(const glm::vec3& color);

    void setIntensity(float intensity);

    void setDirty(bool dirty);
};
