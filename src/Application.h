#pragma once


class Application {
public:
    static const int FPS;
    static const int FRAME_DURATION_NS;

    Application();

    enum class Status {
        SUCCESS,
        ERROR
    };

    Status run();

private:

    void initGLFW() const;

    void initCallbacks() const;

    void initRegistry() const;
};
