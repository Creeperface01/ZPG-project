#ifndef CV1_TEXTURESHADERCOMPONENT_H
#define CV1_TEXTURESHADERCOMPONENT_H


#include "ShaderComponent.h"

#include "../Shader.h"

class TextureShaderComponent : public ShaderComponent {
public:
    static factoryType *factory;

    UniformVariable<GLuint> textureUnitID;

    UniformVariable<GLboolean> hasTexture;

    explicit TextureShaderComponent(Shader *shader);
};


#endif //CV1_TEXTURESHADERCOMPONENT_H
