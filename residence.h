#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "ownableproperty.h"

class Residence : public OwnableProperty {
  public:
    // Constructor to initialize all necessary fields
    Residence(std::string name, int loc, std::shared_ptr<PropertyConfig> config = nullptr, bool owned = false, bool mortgaged = false);
    // Prompts the player to buy the residence if unowned, pay the tuition if owned, or no action if 
    // the player is the owner
    void performAction(Player &p, Bank &b) override;
};
#endif // _RESIDENCE_H
