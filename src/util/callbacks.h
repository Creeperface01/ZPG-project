#pragma once

#include <functional>

class Window;

struct WindowData {
public:
    Window *window;

    explicit WindowData(Window *window) : window(window) {}
};

struct KeyData : public WindowData {
public:
    int key;
    int scanCode;
    int action;
    int mods;

    KeyData(Window *window, int key, int scanCode, int action, int mods)
            : WindowData(window), key(key), scanCode(scanCode), action(action), mods(mods) {}
};

using KeyCallback = std::function<void (const KeyData&)>;

struct ScrollData : public WindowData {
public:
    float offsetX, offsetY;

    ScrollData(Window *window, float offsetX, float offsetY) : WindowData(window), offsetX(offsetX), offsetY(offsetY) {}
};

using ScrollCallback = std::function<void (const ScrollData&)>;

struct CursorData : public WindowData {
public:
    float x, y;

    CursorData(Window *window, float x, float y) : WindowData(window), x(x), y(y) {}
};

using CursorCallback = std::function<void (const CursorData&)>;