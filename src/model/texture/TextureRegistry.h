#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Texture.h"

using TextureId = std::string;

class TextureRegistry {
private:
    static TextureRegistry *_instance;

    std::unordered_map<TextureId, std::unique_ptr<Texture>> _textures;

    void registerDefaultTextures();

    friend class Application;

public:
    static TextureRegistry *get();

    void registerCubeMapTexture(
            const TextureId &textureName,
            GLuint slot,
            GLuint unit,
            const std::string &posX,
            const std::string &negX,
            const std::string &posY,
            const std::string &negY,
            const std::string &posZ,
            const std::string &negZ
    );

    void registerSimpleTexture(
            const TextureId &textureName,
            GLuint slot,
            GLuint unit,
            const std::string &path
    );

    [[nodiscard]] Texture *getTexture(const TextureId &textureId) const;

    std::vector<Texture *> getAll();
};
