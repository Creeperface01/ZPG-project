#pragma once

#include "Buffer.h"

class VertexArrayBuffer : public virtual Buffer {
protected:
    explicit VertexArrayBuffer();

    void generate(GLuint &id) const override;

    void bind() const override;

    void unbind() const override;

    friend class Buffer;
};
