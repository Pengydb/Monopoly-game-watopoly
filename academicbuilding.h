#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"

enum MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class AcademicBuilding : public OwnableProperty {
    int impCount; // number of improvements on building
    int impCost;
    // MonopolyBlock monBlock; getGroup from config
  
  public:
    AcademicBuilding(std::string name, PropertyConfig& config, int impCount, int impCost);
    void performAction(Player &p, School &s) override;
    void addImps(int n); // Increments impCount by n times (charges player impCost*n )
    int getImpCost() const;
    int getImpCount() const;
    void sellImps(int n); // Deincrements impCount by n times (gives player impCost*(0.5)*n )
}; 

#endif // ACADEMICBUILDING_H
