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
    static Shader *loadShader(const std::string &vertexFile, const std::string &fragmentFile);
};
