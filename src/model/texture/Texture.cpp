#include "Texture.h"

#include <SOIL2/SOIL2.h>
#include <exception>
#include <iostream>
#include <vector>
#include <stb_image.h>

#include "../../util/debug.h"

GLenum Texture::getOpenGlTextureType() const {
    switch (_type) {
        case CUBE_MAP:
            return GL_TEXTURE_CUBE_MAP;
        case TEXTURE_2D:
        default:
            return GL_TEXTURE_2D;
    }
}

Texture::Texture(GLuint id, GLuint slot, GLuint unit, Type type) : _id(id), _slot(slot), _unit(unit), _type(type) {}

void Texture::startUsing() {
    debugGlCall(glActiveTexture, _slot);
    debugGlCall(glBindTexture, getOpenGlTextureType(), _id);

    debugGlCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    debugGlCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::stopUsing() {
//    debugGlCall(glBindTexture, GL_TEXTURE_CUBE_MAP, 0);
}

GLuint Texture::getSlot() const {
    return _slot;
}

GLuint Texture::getUnit() const {
    return _unit;
}
