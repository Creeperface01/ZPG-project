#include "TextureShaderComponent.h"

ShaderComponent::factoryType* TextureShaderComponent::factory = ShaderComponent::baseFactory<TextureShaderComponent>();

TextureShaderComponent::TextureShaderComponent(Shader* shader) : ShaderComponent(shader),
                                                                 textureUnitID(
                                                                     shader->makeVariable<GLuint>("textureUnitID")
                                                                 ),
                                                                 hasTexture(
                                                                     shader->makeVariable<GLboolean>("hasTexture")
                                                                 ) {
}
