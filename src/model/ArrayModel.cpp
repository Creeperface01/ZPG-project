#include "ArrayModel.h"

#include "../util/debug.h"

ArrayModel::ArrayModel(const std::vector<ModelAttribute>& vertexAttributes) : BaseModel(vertexAttributes) {
    if (vertexAttributes.empty()) {
        throw std::runtime_error("Cannot create array model with no vertex attributes");
    }

    _vertexCount = vertexAttributes.begin()->getSize();
    assert(_vertexCount > 0 && "Invalid vertex count");
}

void ArrayModel::drawCallback(const Shader &shader) const {
    debugGlCall(
            glDrawArrays,
            GL_TRIANGLES,
            0,
            static_cast<GLsizei>(_vertexCount)
    );
}

//ArrayModel::ArrayModel(
//        const std::string &vertexShaderFile,
//        const std::string &fragmentShaderFile,
//        GLuint size,
//        const void *data
//) : BaseModel(vertexShaderFile, fragmentShaderFile), _vertexCount(size) {
//    _vao->use([this, data, size]() {
//        _vbo = Buffer::create(Buffer::Type::ARRAY);
//        _vbo->setData(size, data);
//
//        this->addAttributeBuffer(_vbo, 0, 3);
//    });
//}
