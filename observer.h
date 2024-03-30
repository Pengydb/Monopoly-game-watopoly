#ifndef __OBSERVER_H_
#define __OBSERVER_H_

// Forward declartion
class Subject;
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(Subject& subject) = 0;
};

#endif // OBSERVER_H
