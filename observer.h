#ifndef __OBSERVER_H_
#define __OBSERVER_H_
#include <memory>
// Forward declartion
class Subject;
class Observer {
public:
    // Default virtual destructor for Observer.
    virtual ~Observer() = default;
    // Pure virtual function to notify the Observer of changes in the Subject.
    virtual void notify(std::shared_ptr<Subject> s) = 0;
};

#endif // OBSERVER_H
