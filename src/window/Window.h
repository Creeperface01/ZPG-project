#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>

#include "../util/glfw_util.h"
#include "../util/callbacks.h"
#include "../io/Keyboard.h"
#include "../io/Cursor.h"
#include "../util/Noncopyable.h"
#include "../scene/Scene.h"
#include "../scene/ObjectRenderer.h"
#include "../scene/Camera.h"

class Scene;

class Window : public Noncopyable {
private:
    static std::unordered_map<GLFWwindow *, Window *> _map;

    unique_ptr_glfw_window _glfwWindow;

    Scene *_scene = nullptr;

    std::vector<KeyCallback> _keyCallbacks;
    std::vector<CursorCallback> _cursorCallbacks;
    std::vector<ScrollCallback> _scrollCallbacks;

    std::unique_ptr<Keyboard> _keyboard;
    std::unique_ptr<Cursor> _cursor;

    void initCallbacks();

    void pollEvents();

    void swapBuffers();

    void clear();

    void checkClosed() const;

public:
    struct properties {
        int width = 1000;
        int height = 600;
        std::string title;
    };

    explicit Window(const properties &properties);

    virtual ~Window();

    void setScene(Scene *scene);

    [[nodiscard]] const Scene *getScene() const;

    void draw();

    void addKeyCallback(const KeyCallback &callback);

    void addCursorCallback(const CursorCallback &callback);

    void addScrollCallback(const ScrollCallback &callback);

    [[nodiscard]] const Keyboard &getKeyboard() const;

    Cursor *getCursor();

    void close();

    [[nodiscard]] bool isClosed() const;

    void clearDepth();
};
