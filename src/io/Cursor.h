#pragma once

#include "../util/Observable.h"

class Window;

class Cursor : public Observable<Cursor> {
public:
    enum Mode {
        NORMAL,
        DISABLED
    };
private:
    Window *_window;

    Mode _mode = DISABLED;

    bool first = true;

    float lastX = 0, lastY = 0, x = 0, y = 0;

public:
    explicit Cursor(Window *window);

    [[nodiscard]] float getLastX() const;

    [[nodiscard]] float getLastY() const;

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    Mode getMode() const;

    void setMode(Mode mode);

    size_t getStencilBufferIndex() const;
};
