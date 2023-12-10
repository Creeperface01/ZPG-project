#include "VertexArrayBuffer.h"

#include "../util/debug.h"

VertexArrayBuffer::VertexArrayBuffer() : Buffer(Buffer::Type::VERTEX_ARRAY) {}

void VertexArrayBuffer::generate(GLuint &id) const {
    debugGlCall(glGenVertexArrays, 1, &id);
}

void VertexArrayBuffer::bind() const {
    debugGlCall(glBindVertexArray, _id);
}

void VertexArrayBuffer::unbind() const {
    debugGlCall(glBindVertexArray, 0);
}
