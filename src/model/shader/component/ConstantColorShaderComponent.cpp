#include "ConstantColorShaderComponent.h"

ShaderComponent::factoryType *ConstantColorShaderComponent::factory = ShaderComponent::baseFactory<ConstantColorShaderComponent>();

ConstantColorShaderComponent::ConstantColorShaderComponent(Shader *shader) : ShaderComponent(shader),
                                                                             color(shader->makeVariable<glm::vec3>(
                                                                                     "color")) {

}
