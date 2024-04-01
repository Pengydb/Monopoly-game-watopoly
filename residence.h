#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "ownableproperty.h"

class Residence : public OwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};
#endif // _RESIDENCE_H
