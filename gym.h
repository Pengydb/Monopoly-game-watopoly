#ifndef _GYM_H_
#define _GYM_H_

#include "ownableproperty.h"

class Bank;

class Gym : public OwnableProperty {
  public:
    Gym(std::string name, int loc, std::shared_ptr<PropertyConfig> config = nullptr, bool owned = false, bool mortgaged = false);
    // Either charges the player for landing on an owned property or prompt the player to buy it if unowned
    void performAction(Player &p, Bank &b) override; 
};

#endif // GYM_H
