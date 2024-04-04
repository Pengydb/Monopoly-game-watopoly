#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "ownableproperty.h"

class Residence : public OwnableProperty
{
public:
  Residence(std::string name, int loc, std::shared_ptr<PropertyConfig> config = nullptr, bool owned, bool mortgaged);
  void performAction(Player &p, Bank &b) override;
};
#endif // _RESIDENCE_H
