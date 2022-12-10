#include "glfw_destructors.h"

void DestroyGLFWWindow::operator()(GLFWwindow *ptr) {
    glfwDestroyWindow(ptr);
}
