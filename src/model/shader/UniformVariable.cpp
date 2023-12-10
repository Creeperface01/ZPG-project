#include "UniformVariable.h"

#include <iostream>
#include "glm/gtx/string_cast.hpp"

template<>
UniformVariable<GLint> &UniformVariable<GLint>::operator=(const GLint &value) {
    checkExists();
    debugGlCall(glUniform1i, _id, value);
    return *this;
}

template<>
UniformVariable<GLuint> &UniformVariable<GLuint>::operator=(const GLuint &value) {
    checkExists();
    debugGlCall(glUniform1ui, _id, value);
    return *this;
}

template<>
UniformVariable<GLfloat> &UniformVariable<GLfloat>::operator=(const GLfloat &value) {
    checkExists();
    debugGlCall(glUniform1f, _id, value);
    return *this;
}

template<>
UniformVariable<glm::vec3> &UniformVariable<glm::vec3>::operator=(const glm::vec3 &value) {
    checkExists();
    debugGlCall(glUniform3fv, _id, 1, &value[0]);
    return *this;
}

template<>
UniformVariable<glm::mat4> &UniformVariable<glm::mat4>::operator=(const glm::mat4 &value) {
    checkExists();
    debugGlCall(glUniformMatrix4fv, _id, 1, GL_FALSE, &value[0][0]);
    return *this;
}

template<>
UniformVariable<GLboolean> &UniformVariable<GLboolean>::operator=(const GLboolean &value) {
    checkExists();
    debugGlCall(glUniform1i, _id, value ? 1 : 0);
    return *this;
}