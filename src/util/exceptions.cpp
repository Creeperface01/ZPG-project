#include "exceptions.h"

#include <utility>

GlfwException::GlfwException(std::string what) : _what(std::move(what)) {}

const char *GlfwException::what() const noexcept {
    return _what.c_str();
}

BufferAlreadyBoundException::BufferAlreadyBoundException(std::string what) : _what(std::move(what)) {

}

const char *BufferAlreadyBoundException::what() const noexcept {
    return _what.c_str();
}
