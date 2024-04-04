#ifndef _GYM_H_
#define _GYM_H_

#include "ownableproperty.h"

class Bank;

class Gym : public OwnableProperty {
  public:
    Gym(std::string name, int loc, std::shared_ptr<PropertyConfig> config = nullptr, bool owned = false, bool mortgaged = false);
    void performAction(Player &p, Bank &b) override; 
};

#endif // GYM_H
