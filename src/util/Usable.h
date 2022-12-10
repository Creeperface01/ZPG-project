#pragma once

#include <functional>

#include "util.h"

template<typename THIS>
class Usable {
public:
    virtual ~Usable() = default;

    virtual void startUsing() {

    }

    virtual void stopUsing() {

    }

    template<typename T>
    T use(const std::function<T(THIS &subject)> &callback) {
        defer([this]() {
            stopUsing();
        });

        startUsing();
        return callback(*static_cast<THIS *>(this));
    }

    template<typename T>
    T use(const std::function<T()> &callback) {
        return use<void>([&callback](THIS &subject) {
            callback();
        });
    }

    void use(const std::function<void(THIS &)> &callback) {
        use<void>([&callback](THIS &s) {
            callback(s);
        });
    }

    void use(const std::function<void()> &callback) {
        use<void>([&callback](THIS &s) {
            callback();
        });
    }
};