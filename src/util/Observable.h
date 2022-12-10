#pragma once

#include <vector>

#include "Observer.h"

template<typename THIS>
class Observable {
private:
    std::vector<Observer<THIS> *> _observers;

protected:
    void notifyObservers() {
        for (Observer<THIS> *item: _observers) {
            item->update(static_cast<THIS *>(this));
        }
    }

public:
    void attach(Observer<THIS> *observer) {
        this->_observers.push_back(observer);
    }

    void detach(Observer<THIS> *observer) {
        std::remove(this->_observers.begin(), this->_observers.end(), observer);
    }
};
