#ifndef __SUBJECT_H_
#define __SUBJECT_H_

#include <vector>
#include <memory>
#include "observer.h"

class Subject {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    // other fields if necessary

public:
    
    void attach(std::shared_ptr<Observer> o); 
    void detach(std::shared_ptr<Observer> o);
    void notifyObservers(); // notify all Observers
    // add more methods if necessary

};

#endif // SUBJECT_H
