#include "TextureObjectComponent.h"

#include "../DrawableObject.h"
#include "../../../model/shader/component/TextureShaderComponent.h"

TextureObjectComponent::TextureObjectComponent(
    Texture* texture,
    bool optional
): _texture(texture), _optional(optional) {
}

void TextureObjectComponent::beforeDraw(DrawableObject* object) {
    _texture->startUsing();

    auto shader = object->getShader();

    auto textureComponent = shader->getComponent<TextureShaderComponent>();
    textureComponent->textureUnitID = _texture->getUnit();

    if (_optional) {
        textureComponent->hasTexture = true;
    }
}

void TextureObjectComponent::afterDraw(DrawableObject* object) {
    auto shader = object->getShader();

    auto textureComponent = shader->getComponent<TextureShaderComponent>();
    if (_optional) {
        textureComponent->hasTexture = false;
    }
}
