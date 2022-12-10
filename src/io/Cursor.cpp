#include "Cursor.h"

#include "../window/Window.h"

Cursor::Cursor(Window &window) {
    window.addCursorCallback([this](const CursorData &data) {
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
