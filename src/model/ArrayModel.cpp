#include "ArrayModel.h"

#include "../util/debug.h"

void ArrayModel::drawCallback(const Shader &shader) {
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
