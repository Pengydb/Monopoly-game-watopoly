#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for(auto o : observers) {
        std::shared_ptr<Subject> sp = shared_from_this();
        if (o) o->notify(sp);
    }
}
