#include "VertexArrayBuffer.h"

#include "../util/debug.h"

VertexArrayBuffer::VertexArrayBuffer() : Buffer(Buffer::Type::VERTEX_ARRAY) {}

void VertexArrayBuffer::generate(GLuint &id) const {
//    ({
//        auto a1 = 1;
//        auto a2 = &id;
//        if constexpr (DEBUG)
//            std::cout << "_file_name_short_" << ":" << 8 << "(" << "_function_name_" << ")" << " - "
//                      << "__glewGenVertexArrays" << "(" << "1" << ", " << "&id" << ")" << " ---> "
//                      << "__glewGenVertexArrays" << "(" << a1 << ", " << a2 << ")" << std::endl;
//        __glewGenVertexArrays(1, &id);
//    })
    debugGlCall(glGenVertexArrays, 1, &id);
//    glGenVertexArrays(1, &id);
}

void VertexArrayBuffer::bind() const {
    debugGlCall(glBindVertexArray, _id);
//    glBindVertexArray(_id);
}

void VertexArrayBuffer::unbind() const {
    debugGlCall(glBindVertexArray, 0);
//    glBindVertexArray(0);
}
