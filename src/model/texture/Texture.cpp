#include "Texture.h"

#include <SOIL2/SOIL2.h>
#include <exception>
#include <vector>
#include <stb_image.h>

#include "../../util/debug.h"

Texture::Texture(GLuint id, GLint slot) : _id(id), _slot(slot) {}

void Texture::startUsing() {
    debugGlCall(glBindTexture, GL_TEXTURE_CUBE_MAP, _id);
}

void Texture::stopUsing() {
//    debugGlCall(glBindTexture, GL_TEXTURE_CUBE_MAP, 0);
}

GLint Texture::getSlot() const {
    return _slot;
}
