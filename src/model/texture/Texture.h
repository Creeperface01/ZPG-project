#pragma once

#include <GL/glew.h>
#include <string>

#include "../../util/Noncopyable.h"
#include "../../util/Usable.h"

class Texture : public Noncopyable, public Usable<Texture> {
public:
    enum Type {
        CUBE_MAP,
        TEXTURE_2D
    };
private:
    GLuint _id;

    GLuint _slot;

    GLuint _unit;

    Type _type;

    GLenum getOpenGlTextureType() const;

public:
    Texture(GLuint id, GLuint slot, GLuint unit, Type type);

    [[nodiscard]] GLuint getSlot() const;

    [[nodiscard]] GLuint getUnit() const;

    void startUsing() override;

    void stopUsing() override;

};
