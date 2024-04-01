#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"

enum MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class AcademicBuilding : public OwnableProperty {
    int impCount; // number of improvements on building
    int impCost; // cost to add improvement
    MonopolyBlock monBlock;
  
  public:
    void performAction(Player &p, School &s) override;
    void addImps(int n); // Increments impCount by n times (charges player impCost*n )
    void sellImps(int n); // Deincrements impCount by n times (gives player impCost*(0.5)*n )
}; 

#endif // ACADEMICBUILDING_H
