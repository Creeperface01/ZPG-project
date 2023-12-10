//
// Created by Jan Bednář on 04.11.2023.
//

#ifndef CV1_TEXTUREOBJECTCOMPONENT_H
#define CV1_TEXTUREOBJECTCOMPONENT_H


#include "ObjectComponent.h"

#include "../../../model/texture/Texture.h"

class CubeMapTextureObjectComponent : public ObjectComponent {
private:
    Texture *_texture;
public:
    explicit CubeMapTextureObjectComponent(Texture *texture);

    void init(DrawableObject *object) override;

    void beforeDraw(DrawableObject *object) override;

    void afterDraw(DrawableObject *object) override;
};


#endif //CV1_TEXTUREOBJECTCOMPONENT_H
