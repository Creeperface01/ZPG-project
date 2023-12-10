#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <functional>
#include <tuple>

#include <glm/mat4x4.hpp>

#include "shader/ShaderLoader.h"
#include "../memory/Buffer.h"
#include "../memory/VertexArrayBuffer.h"
#include "../util/Noncopyable.h"
#include "attribute/ModelAttribute.h"
#include "shader/ShaderRegistry.h"

class BaseModel : public Noncopyable {
private:
    std::vector<std::unique_ptr<Buffer>> _buffers;

protected:
    std::unique_ptr<VertexArrayBuffer> _vao;

public:
    explicit BaseModel(const std::vector<ModelAttribute>& vertexAttributes);

    void addBuffer(Buffer *buffer);

    void addAttributeBuffer(Buffer *buffer, GLuint bufferIndex, GLint components, GLenum type = GL_FLOAT);

    void addAttributeBuffer(Buffer *buffer, GLuint bufferIndex, const ModelAttribute &attribute);

//    void addMultiAttributeBuffer(
//            Buffer *buffer,
//            const std::initializer_list<VertexAttribute> &attributes
//    );

    void draw(const Shader &shader) const;

protected:

    virtual void drawCallback(const Shader &shader) const;

    void useBuffers(const std::function<void()> &callback) const;
};
