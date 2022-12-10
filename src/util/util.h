#pragma once

#include <vector>
#include <iostream>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>

template<typename T>
GLsizeiptr get_vector_size(const std::vector<T> &vec) {
    return static_cast<GLsizeiptr>(vec.size() * sizeof(T));
}

template<typename E>
constexpr auto to_integral(E e) -> typename std::underlying_type<E>::type {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

class deferred_call {
private:
    std::function<void()> _callback;

    bool _executed = false;

public:
    deferred_call(const deferred_call &that) = delete;

    deferred_call &operator=(const deferred_call &that) = delete;

    explicit deferred_call(std::function<void()> callback);

    ~deferred_call();
};

deferred_call defer0(const std::function<void()> &callback);

#ifndef defer
#define defer(func) auto ____defer = defer0(func);
#endif

std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec);