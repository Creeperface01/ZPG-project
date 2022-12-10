#include "TextureRegistry.h"

#include <vector>
#include <stb_image.h>

#include <SOIL2/SOIL2.h>

#include "DefaultTextures.h"

GLuint loadCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        } else {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

TextureRegistry *TextureRegistry::_instance = new TextureRegistry();

void TextureRegistry::registerDefaultTextures() {
    registerCubeMapTexture(
            DefaultTextures::SKY_BOX,
            GL_TEXTURE0,
            "assets/textures/cube/posx.jpg",
            "assets/textures/cube/negx.jpg",
            "assets/textures/cube/posy.jpg",
            "assets/textures/cube/negy.jpg",
            "assets/textures/cube/posz.jpg",
            "assets/textures/cube/negz.jpg"
    );

    registerSimpleTexture(
            DefaultTextures::GRASS,
            GL_TEXTURE1,
            "assets/textures/grass.png"
    );
}

TextureRegistry *TextureRegistry::get() {
    return _instance;
}

Texture *TextureRegistry::getTexture(const TextureId &textureId) const {
    auto it = _textures.find(textureId);

    if (it == _textures.end()) {
        return nullptr;
    }

    return it->second.get();
}

std::vector<Texture *> TextureRegistry::getAll() {
    std::vector<Texture *> r;

    std::transform(
            _textures.begin(),
            _textures.end(),
            r.begin(),
            [](decltype(_textures)::value_type &entry) {
                return entry.second.get();
            }
    );

    return r;
}

void
TextureRegistry::registerCubeMapTexture(
        const TextureId &textureName,
        GLuint slot,
        const std::string &posX,
        const std::string &negX,
        const std::string &posY,
        const std::string &negY,
        const std::string &posZ,
        const std::string &negZ
) {
    assert(!_textures.contains(textureName) && "Texture already registered");
    GLuint id = loadCubemap(
            {
                    posX,
                    negX,
                    posY,
                    negY,
                    posZ,
                    negZ,
            }
    );

    if (id == 0) {
        throw std::runtime_error("Could not load texture");
    }

    _textures[textureName] = std::make_unique<Texture>(id, slot);
}

void TextureRegistry::registerSimpleTexture(const TextureId &textureName, GLuint slot, const std::string &path) {
    assert(!_textures.contains(textureName) && "Texture already registered");

    GLuint id = SOIL_load_OGL_texture(
            path.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y
    );

    if (id == 0) {
        throw std::runtime_error("Could not load texture");
    }

    _textures[textureName] = std::make_unique<Texture>(id, slot);
}
