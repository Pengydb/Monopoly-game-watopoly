#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"
class Player;
class Bank;
enum MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

class AcademicBuilding : public OwnableProperty {
  // number of improvements on building
  int impCount;
  // true if monopoly
  bool monopoly; 

public:
  AcademicBuilding(std::string name, int loc, std::shared_ptr<PropertyConfig> config = nullptr, bool owned = false, bool mortgaged = false, int impCount = 0);
  // Either charges the player for landing on an owned property or prompt the player to buy it if unowned
  void performAction(Player &p, Bank &b) override;
  // Increments impCount by n (DO NOT CHARGE PLAYER)
  void addImps(int n);
  // Returns the improvement cost
  int getImpCost() const;
  // returns whether this is currently a monopoly or not
  bool getMonopoly() const;
  // Changes the state of the monopoly boolean
  void toggleMonopoly();
  // sets whether the building is part of a monopoly or not
  void setMonopoly(bool status);
  // returns the number of improvements
  int getImpCount() const;
    
}; 

#endif // ACADEMICBUILDING_H
