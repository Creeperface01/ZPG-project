#include "CubeMapTextureObjectComponent.h"

#include "../../../model/shader/component/TextureShaderComponent.h"
#include "../DrawableObject.h"

CubeMapTextureObjectComponent::CubeMapTextureObjectComponent(Texture *texture) : _texture(texture) {

}

void CubeMapTextureObjectComponent::init(DrawableObject *object) {

}

void CubeMapTextureObjectComponent::beforeDraw(DrawableObject *object) {
    _texture->startUsing();
    // auto shader = object->getShader();
    //
    // auto textureComponent = shader->getComponent<TextureShaderComponent>();
    // textureComponent->textureUnitID = _texture->getSlot();
}

void CubeMapTextureObjectComponent::afterDraw(DrawableObject *object) {
    _texture->stopUsing();
}
