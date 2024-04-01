#ifndef _ACADEMICBUILDING_H_
#define _ACADEMICBUILDING_H_

#include "ownableproperty.h"

class AcademicBuilding : public OwnableProperty {
  // Monpopoly block is available as a string from OwnableProperty getGroup() method
  // improvement logic handled by school and decorators
  public:
    void performAction(Player &p) override; // will need to use observer pattern to work with board
}; 

#endif // ACADEMICBUILDING_H
