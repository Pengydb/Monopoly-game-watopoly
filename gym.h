#ifndef _GYM_H_
#define _GYM_H_

#include "ownableproperty.h"
#include "bank.h"

class Gym : public OwnableProperty {
  public:
    Gym(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged);
    void performAction(Player &p, Bank &b) override; 
};

#endif // GYM_H
