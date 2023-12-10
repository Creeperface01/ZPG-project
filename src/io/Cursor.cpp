#include "Cursor.h"

#include "../window/Window.h"

Cursor::Cursor(Window* window) : _window(window) {
    window->addCursorCallback([this](const CursorData& data) {
        if (first) {
            x = lastX = data.x;
            y = lastY = data.y;

            first = false;
            return;
        }

        lastX = x;
        lastY = y;

        x = data.x;
        y = data.y;

        this->notifyObservers();
    });
}

float Cursor::getLastX() const {
    return lastX;
}

float Cursor::getLastY() const {
    return lastY;
}

float Cursor::getX() const {
    return x;
}

float Cursor::getY() const {
    return y;
}

Cursor::Mode Cursor::getMode() const {
    return _mode;
}

void Cursor::setMode(Mode mode) {
    _mode = mode;

    auto glfwMode = _mode == Mode::NORMAL ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    debugGlCall(
        glfwSetInputMode,
        _window->getNativeWindow(),
        GLFW_CURSOR,
        glfwMode
    );
}

size_t Cursor::getStencilBufferIndex() const {
    size_t index;

    auto windowProperties = _window->getProperties();
    debugGlCall(
        glReadPixels,
        windowProperties.width / 2,
        windowProperties.height / 2,
        1,
        1,
        GL_STENCIL_INDEX,
        GL_UNSIGNED_INT,
        &index
    );

    return index;
}
