#ifndef __OBSERVER_H_
#define __OBSERVER_H_
#include <memory>
// Forward declartion
class Subject;
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(std::shared_ptr<Subject> s) = 0;
};

#endif // OBSERVER_H
