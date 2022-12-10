#include "BaseModel.h"

#include <functional>

#include <glm/gtx/string_cast.hpp>

#include "shader/ShaderRegistry.h"
#include "../util/debug.h"

void BaseModel::addBuffer(Buffer *buffer) {
    if (auto vb = dynamic_cast<VertexArrayBuffer *>(buffer); vb != nullptr) {
        this->_vao.reset(vb);
        return;
    }

    this->_buffers.emplace_back(buffer);
}

BaseModel::BaseModel(Shader *shader, Texture *texture) : _shader(shader), _texture(texture) {
    this->addBuffer(Buffer::create(Buffer::Type::VERTEX_ARRAY)); // create vao
}

void BaseModel::draw(
        const glm::mat4 &modelMatrix
) {
    _shader->use([this, &modelMatrix](Shader &shader) {
        if (_texture != nullptr) { //TODO: improve
            _texture->startUsing();
            shader.hasTexture = true;
            shader.textureUnitID = _texture->getSlot();
        } else {
            shader.hasTexture = false;
        }

        shader.modelMatrix = modelMatrix;

        _vao->use([this, &shader]() {
            drawCallback(shader);
        });

        if (_texture != nullptr) {
            _texture->stopUsing();
        }
    });
}

void BaseModel::drawCallback(const Shader &shader) {

}

void BaseModel::addAttributeBuffer(Buffer *buffer, GLuint index, GLint components, GLenum type) {
    this->addBuffer(buffer);

    buffer->use([index, components, type]() {
        debugGlCall(glEnableVertexAttribArray, index);
        debugGlCall(glVertexAttribPointer, index, components, type, GL_FALSE, 0, (GLvoid *) nullptr);
    });
}

//void BaseModel::addMultiAttributeBuffer(Buffer *buffer, const std::initializer_list<VertexAttribute> &attributes) {
//    this->addBuffer(buffer);
//
//    buffer->use([&attributes]() {
//        for (const auto &item: attributes) {
//            debugGlCall(glEnableVertexAttribArray, item.index);
//        }
//        debugGlCall(glVertexAttribPointer, index, components, type, GL_FALSE, 0, (GLvoid *) nullptr);
//    });
//}
