#include "ShaderLoader.h"

#include <string>

#include "../../util/debug.h"

std::string loadFile(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << fileName << std::endl;
        //exit(1);
    }
    std::stringstream fileData;
    fileData << file.rdbuf();
    file.close();
    return fileData.str();
}

ShaderLoader::ShaderEntry ShaderLoader::loadShader(const std::string &vertexFile, const std::string &fragmentFile) {
    std::cout << "Shader::loadShader " << vertexFile << " " << fragmentFile << std::endl;

    std::string vertexShaderString = loadFile(vertexFile);
    std::string fragmentShaderString = loadFile(fragmentFile);

    auto vlen = static_cast<GLint>(vertexShaderString.size());
    auto flen = static_cast<GLint>(fragmentShaderString.size());

    if (vertexShaderString.empty()) printf("Empty Vertex Shader\n");
    if (fragmentShaderString.empty()) printf("Empty Fragment Shader\n");

    const char *vertexShaderCStr = vertexShaderString.c_str();
    const char *fragmentShaderCStr = fragmentShaderString.c_str();

    auto vertexID = debugGlCall(glCreateShader, GL_VERTEX_SHADER);    //Vertex Shader
    debugGlCall(glShaderSource, vertexID, 1, (const GLchar **) &vertexShaderCStr, &vlen);
    debugGlCall(glCompileShader, vertexID);
    GLint status;
    debugGlCall(glGetShaderiv, vertexID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        debugGlCall(glGetShaderiv, vertexID, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto strInfoLog = new GLchar[infoLogLength + 1];
        debugGlCall(glGetShaderInfoLog, vertexID, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Compile failure in Vertex shader:\n%s\n", strInfoLog);
        delete[] strInfoLog;
    }

    auto fragmentID = debugGlCall(glCreateShader, GL_FRAGMENT_SHADER); //Fragment Shader
    debugGlCall(glShaderSource, fragmentID, 1, (const GLchar **) &fragmentShaderCStr, &flen);
    debugGlCall(glCompileShader, fragmentID);

    debugGlCall(glGetShaderiv, fragmentID, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        debugGlCall(glGetShaderiv, fragmentID, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto strInfoLog = new GLchar[infoLogLength + 1];
        debugGlCall(glGetShaderInfoLog, fragmentID, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Compile failure in Fragment shader:\n%s\n", strInfoLog);
        delete[] strInfoLog;
    }

    auto shaderProgramID = debugGlCall(glCreateProgram);
    debugGlCall(glAttachShader, shaderProgramID, vertexID);
    debugGlCall(glAttachShader, shaderProgramID, fragmentID);
    debugGlCall(glLinkProgram, shaderProgramID);

    debugGlCall(glGetProgramiv, shaderProgramID, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        debugGlCall(glGetProgramiv, shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);

        auto strInfoLog = new GLchar[infoLogLength + 1];
        debugGlCall(glGetProgramInfoLog, shaderProgramID, infoLogLength, nullptr, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    } else {
        std::cout << "Shader: Load OK" << std::endl;
    }

    return {shaderProgramID, vertexID, fragmentID};
}
