#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"
class Player;
class Bank;

enum MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class AcademicBuilding : public OwnableProperty {
    int impCount; // number of improvements on building
    int impCost;
    bool monopoly; // true if monopoly
    // MonopolyBlock monBlock; getGroup from config
  
  public:
    AcademicBuilding(std::string name, int loc, bool owned, bool mortgaged, int impCount, int impCost);
    void performAction(Player &p, Bank &b) override;
    // Increments impCount by n (DO NOT CHARGE PLAYER)
    void addImps(int n); 
    int getImpCost() const;
    bool getMonopoly() const;
    void toggleMonopoly();
    void setMonopoly(bool status);
    int getImpCount() const;
    
}; 

#endif // ACADEMICBUILDING_H
