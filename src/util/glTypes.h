#ifndef GLTYPES_H
#define GLTYPES_H
#include <GL/glew.h>

template<typename T>
struct glType {
    static GLenum const type;
};

template<>
constexpr GLenum glType<bool>::type = GL_BYTE;

template<>
constexpr GLenum glType<char>::type = GL_BYTE;

template<>
constexpr GLenum glType<unsigned char>::type = GL_UNSIGNED_BYTE;

template<>
constexpr GLenum glType<short>::type = GL_SHORT;

template<>
constexpr GLenum glType<unsigned short>::type = GL_UNSIGNED_SHORT;

template<>
constexpr GLenum glType<int>::type = GL_INT;

template<>
constexpr GLenum glType<unsigned int>::type = GL_UNSIGNED_INT;

template<>
constexpr GLenum glType<float>::type = GL_FLOAT;

template<>
constexpr GLenum glType<double>::type = GL_DOUBLE;

#endif //GLTYPES_H
