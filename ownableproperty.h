#ifndef _OWNABLEPROPERTY_H_
#define _OWNABLEPROPERTY_H_

#include "tile.h"
#include "propertyconfig.h"
#include <string>

class OwnableProperty : public Tile {
    bool owned;      // True if property is owned, false otherwise
    bool mortgaged;  // True if property is mortgaged, false otherwise
  protected:
  std::shared_ptr<PropertyConfig> config;
  

  public:
    OwnableProperty(std::string name, int loc, std::shared_ptr<PropertyConfig> = nullptr, bool owned = false, bool mortgaged = false);
    // Performs action when player lands on an ownable property 
    // 1) Prompts player to buy if unowned.
    //    -  If player can't afford or doens't buy, property goes up for auction
    // 2) Charges player a fee if owned and not mortgaged
    //    -  If player can't afford to pay fee, then they can declare bankrupcy, 
    // try selling any of their assets, or try and trade (if they have property)
   void performAction(Player &p, Bank &b) override = 0;

    // Returns owned field
    bool isOwned() const; 
    // returns mortgage field
    bool isMortgaged() const; 
    // Returns cost field from config
    int getCost() const;
    // Returns which monopoly this property belongs to
    std::string getGroup() const;
    // Toggles mortgaged field to opposite of what it was
    void toggleMortgage(); 
    // Toggles owned field to opposite of what it was
    void toggleOwnership(); 

    // Return shared_ptr to config
    std::shared_ptr<PropertyConfig> getConfig() const; 
    // Updates config shared_ptr field to newConfig
    void setConfig(const std::shared_ptr<PropertyConfig> newConfig); // Sets config

};

#endif // OWNABLEPROPERTY_H
