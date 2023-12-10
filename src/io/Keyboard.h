#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "../util/Observable.h"

class Window;

class Keyboard {
public:
    class KeyCode {
    private:
        GLint _code;

    public:
        explicit constexpr KeyCode(const GLint code) noexcept: _code(code) {}

        constexpr bool operator==(const KeyCode &rhs) const {
            return _code == rhs._code;
        }

        constexpr bool operator!=(const KeyCode &rhs) const {
            return !(rhs == *this);
        }

        [[nodiscard]] constexpr GLint toGlfwCode() const {
            return _code;
        }
    };

    template<typename THIS>
    class KeyboardAction : public Observable<THIS> {
    public:
        KeyCode _code;

        explicit KeyboardAction(const KeyCode &code) : _code(code) {}

        void update(const KeyCode &code) {
            this->_code = code;

            this->notifyObservers();
        }
    };

    class Press : public KeyboardAction<Press> {
    public:
        explicit Press(const KeyCode &code);
    };

    class Release : public KeyboardAction<Release> {
    public:
        explicit Release(const KeyCode &code);
    };

    class Hold : public KeyboardAction<Hold> {
    public:
        explicit Hold(const KeyCode &code);
    };

    static Press PRESS;

    static Release RELEASE;

    static Hold HOLD;

    explicit Keyboard(Window &window);

};

namespace KeyCodes {

    inline constexpr Keyboard::KeyCode unknown{GLFW_KEY_UNKNOWN};


    inline constexpr Keyboard::KeyCode a{GLFW_KEY_A};
    inline constexpr Keyboard::KeyCode b{GLFW_KEY_B};
    inline constexpr Keyboard::KeyCode c{GLFW_KEY_C};
    inline constexpr Keyboard::KeyCode d{GLFW_KEY_D};
    inline constexpr Keyboard::KeyCode e{GLFW_KEY_E};
    inline constexpr Keyboard::KeyCode f{GLFW_KEY_F};
    inline constexpr Keyboard::KeyCode g{GLFW_KEY_G};
    inline constexpr Keyboard::KeyCode h{GLFW_KEY_H};
    inline constexpr Keyboard::KeyCode i{GLFW_KEY_I};
    inline constexpr Keyboard::KeyCode j{GLFW_KEY_J};
    inline constexpr Keyboard::KeyCode k{GLFW_KEY_K};
    inline constexpr Keyboard::KeyCode l{GLFW_KEY_L};
    inline constexpr Keyboard::KeyCode m{GLFW_KEY_M};
    inline constexpr Keyboard::KeyCode n{GLFW_KEY_N};
    inline constexpr Keyboard::KeyCode o{GLFW_KEY_O};
    inline constexpr Keyboard::KeyCode p{GLFW_KEY_P};
    inline constexpr Keyboard::KeyCode q{GLFW_KEY_Q};
    inline constexpr Keyboard::KeyCode r{GLFW_KEY_R};
    inline constexpr Keyboard::KeyCode s{GLFW_KEY_S};
    inline constexpr Keyboard::KeyCode t{GLFW_KEY_T};
    inline constexpr Keyboard::KeyCode u{GLFW_KEY_U};
    inline constexpr Keyboard::KeyCode v{GLFW_KEY_V};
    inline constexpr Keyboard::KeyCode w{GLFW_KEY_W};
    inline constexpr Keyboard::KeyCode x{GLFW_KEY_X};
    inline constexpr Keyboard::KeyCode y{GLFW_KEY_Y};
    inline constexpr Keyboard::KeyCode z{GLFW_KEY_Z};

    inline constexpr Keyboard::KeyCode one{GLFW_KEY_1};
    inline constexpr Keyboard::KeyCode two{GLFW_KEY_2};
    inline constexpr Keyboard::KeyCode three{GLFW_KEY_3};
    inline constexpr Keyboard::KeyCode four{GLFW_KEY_4};
    inline constexpr Keyboard::KeyCode five{GLFW_KEY_5};
    inline constexpr Keyboard::KeyCode six{GLFW_KEY_6};
    inline constexpr Keyboard::KeyCode seven{GLFW_KEY_7};
    inline constexpr Keyboard::KeyCode eight{GLFW_KEY_8};
    inline constexpr Keyboard::KeyCode nine{GLFW_KEY_9};
    inline constexpr Keyboard::KeyCode zero{GLFW_KEY_0};

    inline constexpr Keyboard::KeyCode f1{GLFW_KEY_F1};
    inline constexpr Keyboard::KeyCode f2{GLFW_KEY_F2};
    inline constexpr Keyboard::KeyCode f3{GLFW_KEY_F3};
    inline constexpr Keyboard::KeyCode f4{GLFW_KEY_F4};
    inline constexpr Keyboard::KeyCode f5{GLFW_KEY_F5};
    inline constexpr Keyboard::KeyCode f6{GLFW_KEY_F6};
    inline constexpr Keyboard::KeyCode f7{GLFW_KEY_F7};
    inline constexpr Keyboard::KeyCode f8{GLFW_KEY_F8};
    inline constexpr Keyboard::KeyCode f9{GLFW_KEY_F9};
    inline constexpr Keyboard::KeyCode f10{GLFW_KEY_F10};
    inline constexpr Keyboard::KeyCode f11{GLFW_KEY_F11};
    inline constexpr Keyboard::KeyCode f12{GLFW_KEY_F12};

    inline constexpr Keyboard::KeyCode left{GLFW_KEY_LEFT};
    inline constexpr Keyboard::KeyCode right{GLFW_KEY_RIGHT};
    inline constexpr Keyboard::KeyCode up{GLFW_KEY_UP};
    inline constexpr Keyboard::KeyCode down{GLFW_KEY_DOWN};

    inline constexpr Keyboard::KeyCode space{GLFW_KEY_SPACE};
    inline constexpr Keyboard::KeyCode enter{GLFW_KEY_ENTER};
    inline constexpr Keyboard::KeyCode escape{GLFW_KEY_ESCAPE};
    inline constexpr Keyboard::KeyCode backspace{GLFW_KEY_BACKSPACE};
    inline constexpr Keyboard::KeyCode tab{GLFW_KEY_TAB};

    inline constexpr Keyboard::KeyCode caps_lock{GLFW_KEY_CAPS_LOCK};
    inline constexpr Keyboard::KeyCode left_shift{GLFW_KEY_LEFT_SHIFT};
    inline constexpr Keyboard::KeyCode right_shift{GLFW_KEY_RIGHT_SHIFT};
    inline constexpr Keyboard::KeyCode left_ctrl{GLFW_KEY_LEFT_CONTROL};
    inline constexpr Keyboard::KeyCode right_ctrl{GLFW_KEY_RIGHT_CONTROL};
    inline constexpr Keyboard::KeyCode left_alt{GLFW_KEY_LEFT_ALT};
    inline constexpr Keyboard::KeyCode right_alt{GLFW_KEY_RIGHT_ALT};

}