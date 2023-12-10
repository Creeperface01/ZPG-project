#pragma once
//GLEW - The OpenGL Extension Wrangler Library
#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Shader.h"

class ShaderLoader {

public:
    struct ShaderEntry {
        GLuint _programId;
        GLuint _vertexId;
        GLuint _fragmentId;
    };

    static ShaderEntry loadShader(const std::string &vertexFile, const std::string &fragmentFile);
};
