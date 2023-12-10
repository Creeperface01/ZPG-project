#include <GL/glew.h>

#include <memory>
#include "Window.h"

std::unordered_map<GLFWwindow *, Window *> Window::_map;

Window::Window(const properties& properties) : _glfwWindow(
                                                   debugGlCall(
                                                       glfwCreateWindow,
                                                       properties.width,
                                                       properties.height,
                                                       properties.title.c_str(),
                                                       nullptr,
                                                       nullptr
                                                   )
                                               ), _properties(properties) {
    if (_glfwWindow == nullptr) {
        throw GlfwException("Could not initialize new glfw window");
    }

    _map.insert({_glfwWindow.get(), this});

    debugGlCall(glfwMakeContextCurrent, _glfwWindow.get());
    debugGlCall(glfwSwapInterval, 1);

    glewExperimental = GL_TRUE;
    debugGlCall(glewInit);

    int width, height;
    debugGlCall(glfwGetFramebufferSize, _glfwWindow.get(), &width, &height);
    debugGlCall(glViewport, 0, 0, width, height);

    initCallbacks();

    debugGlCall(glEnable, GL_TEXTURE_CUBE_MAP_SEAMLESS);
    debugGlCall(glEnable, GL_DEPTH_TEST);
    debugGlCall(glEnable, GL_STENCIL_TEST);

    debugGlCall(glStencilOp, GL_KEEP, GL_KEEP, GL_REPLACE);

    _keyboard = std::make_unique<Keyboard>(*this);

    _cursor = std::make_unique<Cursor>(this);
    _cursor->setMode(Cursor::DISABLED);
}

void Window::setScene(Scene* scene) {
    if (scene == this->_scene) {
        return;
    }

    if (this->_scene != nullptr) {
        this->_scene->onHide();
    }

    this->_scene = scene;
    this->_scene->onShow();
}

const Scene* Window::getScene() const {
    return _scene;
}

void Window::draw() {
    checkClosed();

    clear();

    if (_scene != nullptr) {
        _scene->draw();
    }

    pollEvents();
    swapBuffers();
}

void Window::addKeyCallback(const KeyCallback& callback) {
    this->_keyCallbacks.push_back(callback);
}

void Window::addScrollCallback(const ScrollCallback& callback) {
    this->_scrollCallbacks.push_back(callback);
}

void Window::addCursorCallback(const CursorCallback& callback) {
    this->_cursorCallbacks.push_back(callback);
}

void Window::initCallbacks() {
    glfwSetCursorPosCallback(
        _glfwWindow.get(),
        [](GLFWwindow* glfwWindow, double x, double y) -> void {
            auto window = _map[glfwWindow];

            for (const auto& item: window->_cursorCallbacks) {
                item(
                    {
                        window,
                        static_cast<float>(x),
                        static_cast<float>(y)
                    }
                );
            }
        }
    );

    glfwSetKeyCallback(
        _glfwWindow.get(),
        [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) -> void {
            auto window = _map[glfwWindow];

            for (const auto& item: window->_keyCallbacks) {
                item(
                    {
                        window,
                        key,
                        scancode,
                        action,
                        mods
                    }
                );
            }
        }
    );

    glfwSetScrollCallback(
        _glfwWindow.get(),
        [](GLFWwindow* glfwWindow, double xOffset, double yOffset) -> void {
            auto window = _map[glfwWindow];

            for (const auto& item: window->_scrollCallbacks) {
                item(
                    {
                        window,
                        static_cast<float>(xOffset),
                        static_cast<float>(yOffset)
                    }
                );
            }
        }
    );

    Keyboard::PRESS.attach([this](Keyboard::Press *action) {
        if(action->_code == KeyCodes::c) {
            auto newMode = _cursor->getMode() == Cursor::NORMAL ? Cursor::DISABLED : Cursor::NORMAL;
            _cursor->setMode(newMode);
        }
    });

    glfwSetWindowSizeCallback(_glfwWindow.get(), [](GLFWwindow* glfwWindow, int width, int height) {
        auto window = _map[glfwWindow];
        debugGlCall(glViewport, 0, 0, width, height);

        window->_properties.width = width;
        window->_properties.height = height;
    });
}

Window::~Window() {
    _map.erase(_glfwWindow.get());
}

const Keyboard& Window::getKeyboard() const {
    return *_keyboard;
}

Cursor* Window::getCursor() {
    return _cursor.get();
}

void Window::pollEvents() {
    debugGlCall(glfwPollEvents);
}

void Window::swapBuffers() {
    debugGlCall(glfwSwapBuffers, _glfwWindow.get());
}

void Window::clear() {
    debugGlCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::clearDepth() {
    debugGlCall(glClear, GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::getNativeWindow() const {
    return _glfwWindow.get();
}

const Window::properties Window::getProperties() const {
    return _properties;
}

void Window::close() {
    debugGlCall(glfwSetWindowShouldClose, _glfwWindow.get(), GL_TRUE);
}

bool Window::isClosed() const {
    return debugGlCall(glfwWindowShouldClose, _glfwWindow.get());
}

void Window::checkClosed() const {
    if (isClosed()) {
        throw std::runtime_error("Window has been closed");
    }
}
