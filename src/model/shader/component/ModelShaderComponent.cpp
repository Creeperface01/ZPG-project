#include "ModelShaderComponent.h"
#include "../Shader.h"

ShaderComponent::factoryType *ModelShaderComponent::factory = ShaderComponent::baseFactory<ModelShaderComponent>();

ModelShaderComponent::ModelShaderComponent(Shader *shader)
        : ShaderComponent(shader),
        modelMatrix(shader->makeVariable<glm::mat4>("modelMatrix")) {}
