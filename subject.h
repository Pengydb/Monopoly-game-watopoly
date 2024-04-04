#ifndef __SUBJECT_H_
#define __SUBJECT_H_

#include <vector>
#include <memory>
#include "observer.h"

class Subject : public std::enable_shared_from_this<Subject> {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    // other fields if necessary

public:
    virtual ~Subject() {}
    virtual void attach(std::shared_ptr<Observer> o); 
    virtual void notifyObservers(); // notify all Observers
    // add more methods if necessary

};

#endif // SUBJECT_H
