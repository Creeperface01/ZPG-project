#pragma once


class Application {
public:
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
