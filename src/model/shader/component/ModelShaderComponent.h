

#ifndef CV1_MODELSHADERCOMPONENT_H
#define CV1_MODELSHADERCOMPONENT_H


#include "ShaderComponent.h"
#include "glm/mat4x4.hpp"
#include "../UniformVariable.h"

class ModelShaderComponent : public ShaderComponent {
public:
    static factoryType *factory;

    UniformVariable<glm::mat4> modelMatrix;

    explicit ModelShaderComponent(Shader *shader);
};


#endif //CV1_MODELSHADERCOMPONENT_H
