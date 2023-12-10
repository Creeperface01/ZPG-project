#ifndef CV1_SHADERCOMPONENT_H
#define CV1_SHADERCOMPONENT_H

#include "../../../util/constructor.h"

class Shader;
class ShaderComponent {
protected:
    Shader *_shader;
public:
    using factoryType = decltype(construct_with<ShaderComponent, Shader *>);

    explicit ShaderComponent(Shader *shader);

    virtual ~ShaderComponent() = default;

protected:
    template<typename T>
    static ShaderComponent::factoryType *baseFactory() {
        return construct_as_with<T, ShaderComponent, Shader *>;
    }
};


#endif //CV1_SHADERCOMPONENT_H
