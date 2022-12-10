#pragma once

#include <exception>
#include <string>

class GlfwException : std::exception {
private:
    std::string _what;

public:
    explicit GlfwException(std::string what);

    [[nodiscard]] const char * what() const noexcept override;
};

class BufferAlreadyBoundException : std::exception {
private:
    std::string _what;

public:
    explicit BufferAlreadyBoundException(std::string what);

    [[nodiscard]] const char * what() const noexcept override;
};