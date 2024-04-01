#ifndef _OWNABLEPROPERTY_H_
#define _OWNABLEPROPERTY_H_

#include "tile.h"
#include "propertyconfig.h"
#include <string>

class OwnableProperty : public Tile {
  protected:
    PropertyConfig& config;

  public:
    OwnableProperty(PropertyConfig& config);
    // Performs action when player lands on an ownable property 
    // 1) Prompts player to buy if unowned.
    //    -  If player can't afford or doens't buy, property goes up for auction
    // 2) Charges player a fee if owned and not mortgaged
    //    -  If player can't afford to pay fee, then they can declare bankrupcy, 
    // try selling any of their assets, or try and trade (if they have property)
    virtual void performAction(Player &p) = 0; 

    virtual int getCost() const; // Returns cost 
    virtual int getFee() const; // Returns tuition fee for this property
    virtual std::string getGroup() const; // returns which monopoly this property belongs to
    
    virtual int getDepth() const; // 0 for default, 1 for monopoly, 2 for 1 house . . .
    virtual bool isPropertyEnhancement() const;

    const PropertyConfig& getConfig() const;
};

#endif // OWNABLEPROPERTY_H
