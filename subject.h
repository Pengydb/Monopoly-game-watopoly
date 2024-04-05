#ifndef __SUBJECT_H_
#define __SUBJECT_H_

#include <vector>
#include <memory>
#include "observer.h"

class Subject : public std::enable_shared_from_this<Subject> {
private:
    // Stores smart pointers to all observers
    std::vector<std::shared_ptr<Observer>> observers;

public:
    // Ensures proper destruction of derived classes
    virtual ~Subject() {}
    // Attaches an Observer to the Subject
    virtual void attach(std::shared_ptr<Observer> o);
    // notify all Observers
    virtual void notifyObservers(); 

};

#endif // SUBJECT_H
