#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"

enum MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class AcademicBuilding : public OwnableProperty {
    int impCount; // number of improvements on building
    int impCost;
    bool monopoly; // true if monopoly
    // MonopolyBlock monBlock; getGroup from config
  
  public:
    AcademicBuilding(std::string name, PropertyConfig& config, bool owned, bool mortgaged, int impCount, int impCost);
    void performAction(Player &p, Bank &b) override;
    void addImps(int n); // Increments impCount by n (does not charge player)
    int getImpCost() const;
    bool getMonopoly() const;
    void toggleMonopoly();
    void setMonopoly(bool status);
    int getImpCount() const;
    void sellImps(int n); // Deincrements impCount by n times (gives player impCost*(0.5)*n )
}; 

#endif // ACADEMICBUILDING_H
