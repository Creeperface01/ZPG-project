#pragma once

#include <memory>

#include "glfw_destructors.h"

using unique_ptr_glfw_window = std::unique_ptr<GLFWwindow, DestroyGLFWWindow>;