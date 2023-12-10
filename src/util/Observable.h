#pragma once

#include <vector>
#include <functional>

#include "Observer.h"

template<typename THIS>
class Observable {
public:
    using ObserverCallback = std::function<void (THIS*)>;
private:
    std::vector<Observer<THIS*> *> _observers;
    std::vector<const ObserverCallback> _callableObservers;

protected:
    void notifyObservers() {
        for (Observer<THIS*> *item: _observers) {
            item->update(static_cast<THIS *>(this));
        }

        for (const auto &item: _callableObservers) {
            item(static_cast<THIS *>(this));
        }
    }

public:
    void attach(Observer<THIS*> *observer) {
        this->_observers.push_back(observer);
    }

    void detach(Observer<THIS*> *observer) {
        std::remove(this->_observers.begin(), this->_observers.end(), observer);
    }

    void attach(const ObserverCallback &observer) {
        this->_callableObservers.push_back(observer);
    }

    void detach(const ObserverCallback &observer) {
        std::remove(this->_callableObservers.begin(), this->_callableObservers.end(), observer);
    }
};
