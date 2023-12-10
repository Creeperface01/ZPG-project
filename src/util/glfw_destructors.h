#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct DestroyGLFWWindow {

    void operator()(GLFWwindow *ptr);

};