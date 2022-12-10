#pragma once

#include <GL/glew.h>
#include <string>

#include "../../util/Noncopyable.h"
#include "../../util/Usable.h"

class Texture : public Noncopyable, public Usable<Texture> {
private:
    GLuint _id;

    GLint _slot;

public:
    explicit Texture(GLuint id, GLint slot);

    [[nodiscard]] GLint getSlot() const;

    void startUsing() override;

    void stopUsing() override;

};
