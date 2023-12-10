

#ifndef TEXTUREOBJECTCOMPONENT_H
#define TEXTUREOBJECTCOMPONENT_H
#include "ObjectComponent.h"

#include "../../../model/texture/Texture.h"

class TextureObjectComponent : public ObjectComponent {
private:
    Texture *_texture;
    bool _optional;
public:
    explicit TextureObjectComponent(Texture* texture, bool optional = true);

    void beforeDraw(DrawableObject* object) override;

    void afterDraw(DrawableObject* object) override;
};



#endif //TEXTUREOBJECTCOMPONENT_H
