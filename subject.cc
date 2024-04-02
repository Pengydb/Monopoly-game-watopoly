#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for(auto o : observers) {
        std::shared_ptr<Observer> p = o.lock();
        if (p) p->notify(*this);
    }
}