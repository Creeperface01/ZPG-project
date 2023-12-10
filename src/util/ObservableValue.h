

#ifndef CV1_OBSERVABLEVALUE_H
#define CV1_OBSERVABLEVALUE_H

#include <type_traits>
#include <vector>
#include <functional>

#include "Noncopyable.h"
#include "Observable.h"

template<typename T>
class ObservableValue  : public Noncopyable {
public:
    using ObserverCallback = std::function<void(const T&)>;

private:
    std::vector<Observer<T> *> _observers;
    std::vector<const ObserverCallback> _callbackObservers;

protected:
    T _value;

    void notifyObservers() {
        for (Observer<T> *item: _observers) {
            item->update(_value);
        }

        for (const auto &item: _callbackObservers) {
            item(_value);
        }
    }
public:
    explicit ObservableValue(T value) : _value(value) {}

    explicit ObservableValue() = default;

    void attach(Observer<T> *observer) {
        this->_observers.push_back(observer);
    }

    void detach(Observer<T> *observer) {
        std::remove(this->_observers.begin(), this->_observers.end(), observer);
    }

    void attach(const ObserverCallback &observer) {
        this->_callbackObservers.push_back(observer);
    }

    void detach(const ObserverCallback &observer) {
        std::remove(this->_callbackObservers.begin(), this->_observers.end(), observer);
    }

    ObservableValue<T> &operator=(const T &value) {
        this->_value = value;
        notifyObservers();
        return *this;
    }

    T &get() {
        return _value;
    }

    operator T&() { // NOLINT(*-explicit-constructor)
        return _value;
    }

    T* operator->() {
        return &_value;
    }
};


#endif //CV1_OBSERVABLEVALUE_H
