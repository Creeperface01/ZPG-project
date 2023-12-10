#include "Buffer.h"
#include "VertexArrayBuffer.h"

#include "../util/debug.h"

std::unordered_map<Buffer::Type, std::mutex> Buffer::_bindLock;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"

Buffer::Buffer(Buffer::Type type) : _type(type) {
}

#pragma clang diagnostic pop

Buffer::Type Buffer::getType() const {
    return _type;
}

const GLfloat vertices[] = {
    -1, 0, 0,
    1, 0, 0,
    0, 1, 0
};

void Buffer::setData(size_t size, const void* data) {
    if (_type == Type::VERTEX_ARRAY) {
        throw std::runtime_error("Unsupported buffer type");
    }

    use([this, size, data]() {
        debugGlCall(
            glBufferData,
            to_integral(this->_type),
            static_cast<GLsizeiptr>(size),
            data,
            GL_STATIC_DRAW
        );
    });
}

void Buffer::startUsing() {
    if (!_bindLock.contains(_type)) {
        _bindLock.emplace(std::piecewise_construct, std::make_tuple(_type), std::make_tuple());
    }

    auto& mutex = _bindLock[_type];
    if (!mutex.try_lock()) {
        throw BufferAlreadyBoundException("Buffer type " + std::to_string(to_integral(_type)) + "already bound");
    }

    bind();
}

void Buffer::stopUsing() {
    _bindLock[_type].unlock();
    unbind();
}

Buffer::~Buffer() {
    debugGlCall(glDeleteBuffers, 1, &_id);;
    //    glDeleteBuffers(1, &_id);
}

void Buffer::generate(GLuint& id) const {
    debugGlCall(glGenBuffers, 1, &id);
    //    glGenBuffers(1, &id);
}

void Buffer::bind() const {
    debugGlCall(glBindBuffer, to_integral(this->_type), _id);
    //    glBindBuffer(to_integral(this->_type), _id);
}

void Buffer::unbind() const {
    debugGlCall(glBindBuffer, to_integral(this->_type), 0);
    //    glBindBuffer(to_integral(this->_type), 0);
}

Buffer* Buffer::create(const Buffer::Type& type) {
    Buffer* buf;
    if (type == Type::VERTEX_ARRAY) {
        buf = new VertexArrayBuffer();
    } else {
        buf = new Buffer(type);
    }

    buf->generate(buf->_id);

    return buf;
}
