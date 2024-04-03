#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "ownableproperty.h"

class Residence : public OwnableProperty {
  public:
    Residence(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged);
    void performAction(Player &p, School &s) override;
};
#endif // _RESIDENCE_H
