#include "BaseModel.h"

#include "shader/ShaderRegistry.h"

BaseModel::BaseModel(const std::vector<ModelAttribute>& vertexAttributes) {
    this->addBuffer(Buffer::create(Buffer::Type::VERTEX_ARRAY)); // create vao

    _vao->use([this, &vertexAttributes]() {
        int i = 0;
        for (const auto& attribute: vertexAttributes) {
            const auto buffer = Buffer::create(Buffer::Type::ARRAY);
            buffer->setData(
                attribute.getByteSize(),
                attribute.getData()
            );

            this->addAttributeBuffer(buffer, i++, attribute);
        }
    });
}

void BaseModel::addBuffer(Buffer* buffer) {
    if (auto vb = dynamic_cast<VertexArrayBuffer *>(buffer); vb != nullptr) {
        this->_vao.reset(vb);
        return;
    }

    this->_buffers.emplace_back(buffer);
}

void BaseModel::draw(const Shader& shader) const {
    _vao->use([this, &shader]() {
        drawCallback(shader);
    });
}

void BaseModel::drawCallback(const Shader& shader) const {
}

void BaseModel::addAttributeBuffer(Buffer* buffer, GLuint bufferIndex, GLint components, GLenum type) {
    this->addBuffer(buffer);

    buffer->use([bufferIndex, components, type]() {
        debugGlCall(glEnableVertexAttribArray, bufferIndex);
        debugGlCall(glVertexAttribPointer, bufferIndex, components, type, GL_FALSE, 0, (GLvoid *) nullptr);
    });
}

void BaseModel::addAttributeBuffer(Buffer* buffer, GLuint bufferIndex, const ModelAttribute& attribute) {
    this->addBuffer(buffer);

    buffer->use([bufferIndex, attribute]() {
        debugGlCall(glEnableVertexAttribArray, bufferIndex);
        debugGlCall(
            glVertexAttribPointer,
            bufferIndex,
            attribute.getComponents(),
            attribute.getType(),
            GL_FALSE,
            0,
            (GLvoid *) nullptr
        );
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
