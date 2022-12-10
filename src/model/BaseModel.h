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
#include "shader/ShaderRegistry.h"
#include "texture/Texture.h"

class BaseModel : public Noncopyable {
private:
    std::vector<std::unique_ptr<Buffer>> _buffers;

    Shader *_shader;

    Texture *_texture;

protected:
    std::unique_ptr<VertexArrayBuffer> _vao;

public:
//    struct VertexAttribute {
//        GLuint index;
//        GLint components;
//        GLenum type = GL_FLOAT;
//    };

    explicit BaseModel(Shader *shader, Texture *texture = nullptr);

    void addBuffer(Buffer *buffer);

    void addAttributeBuffer(Buffer *buffer, GLuint index, GLint components, GLenum type = GL_FLOAT);

//    void addMultiAttributeBuffer(
//            Buffer *buffer,
//            const std::initializer_list<VertexAttribute> &attributes
//    );

    void draw(
            const glm::mat4 &modelMatrix
    );

protected:

    virtual void drawCallback(const Shader &shader);

    void useBuffers(const std::function<void()> &callback) const;
};
