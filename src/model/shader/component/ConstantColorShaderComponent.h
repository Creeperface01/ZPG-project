#ifndef CV1_CONSTANTCOLORSHADERCOMPONENT_H
#define CV1_CONSTANTCOLORSHADERCOMPONENT_H


#include "ShaderComponent.h"

#include "../Shader.h"

#include <glm/vec3.hpp>

class ConstantColorShaderComponent : public ShaderComponent {
public:
    static factoryType *factory;

    UniformVariable<glm::vec3> color;

    explicit ConstantColorShaderComponent(Shader *shader);
};


#endif //CV1_CONSTANTCOLORSHADERCOMPONENT_H
