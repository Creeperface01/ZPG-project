#ifndef CV1_CONSTRUCTOR_H
#define CV1_CONSTRUCTOR_H

#include <memory>
#include <utility>
#include <functional>

template<class T>
T *construct(auto &&... u) {
    return new T(std::forward<decltype(u)>(u)...);
}

template<class T, class... U>
T *construct_with(U &&... u) {
    return new T(std::forward<U>(u)...);
}

template<class T, class R, class... U>
R *construct_as_with(U &&... u) {
    return dynamic_cast<R*>(new T(std::forward<U>(u)...));
}

#endif //CV1_CONSTRUCTOR_H
