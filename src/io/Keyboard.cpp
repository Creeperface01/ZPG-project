#include "Keyboard.h"

#include "../window/Window.h"

Keyboard::Press Keyboard::PRESS{KeyCodes::unknown};

Keyboard::Release Keyboard::RELEASE{KeyCodes::unknown};

Keyboard::Hold Keyboard::HOLD{KeyCodes::unknown};

Keyboard::Keyboard(Window &window) {
    window.addKeyCallback([](const KeyData &data) {
        Keyboard::KeyCode keyCode{data.key};

        switch (data.action) {
            case GLFW_PRESS:
                PRESS.update(keyCode);
                break;
            case GLFW_RELEASE:
                RELEASE.update(keyCode);
                break;
            case GLFW_REPEAT:
                HOLD.update(keyCode);
                break;
        }
    });
}

Keyboard::Press::Press(const Keyboard::KeyCode &code) : KeyboardAction(code) {}

Keyboard::Release::Release(const Keyboard::KeyCode &code) : KeyboardAction(code) {}

Keyboard::Hold::Hold(const Keyboard::KeyCode &code) : KeyboardAction(code) {}

