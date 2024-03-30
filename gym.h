#ifndef _GYM_H_
#define _GYM_H_

#include "ownableproperty.h"

class Gym : public OwnableProperty {
    int multiplyer; // Multiplyer that will be used to calculate fee (4 if one Gym owned, 10 if two owned)

  public:
    void performAction() override; 
    void setMultiplier(int m); // sets multiplyer field to m

};

#endif // GYM_H
