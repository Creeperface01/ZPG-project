#include "util.h"

#include <utility>
#include "debug.h"

std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
    os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

void check_gl_error() {
    if (!DEBUG) {
        return;
    }
    const GLuint err = glGetError();
    if (err != GL_NO_ERROR) {
        throw std::runtime_error("GL ERROR: " + std::to_string(err));
    }
}

deferred_call defer0(const std::function<void()>& callback) {
    return deferred_call(callback);
}

deferred_call::deferred_call(std::function<void()> callback) : _callback(std::move(callback)) {
}

deferred_call::~deferred_call() {
    if (!_executed) {
        _executed = true;

        this->_callback();
    }
}
