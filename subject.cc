#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for (auto it = observers.begin(); it != observers.end();) {
        if (auto observer = it->lock()) {
            observer->notify(shared_from_this());
            ++it;
        } else {
            it = observers.erase(it);
        }
    }
}

