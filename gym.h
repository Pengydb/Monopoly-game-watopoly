#ifndef _GYM_H_
#define _GYM_H_

#include "ownableproperty.h"

class Gym : public OwnableProperty {
  public:
    void performAction(Player &p, School &s) override; 
};

#endif // GYM_H
