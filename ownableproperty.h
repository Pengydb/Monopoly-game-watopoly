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

    bool isOwned() const; // Returns owned field
    bool isMortgaged() const; // returns mortgage field
    int getCost() const; // Returns cost field from config
    virtual int getFee() const; // Returns tuition fee for this property
    std::string getGroup() const; // returns which monopoly this property belongs to
    
    void toggleMortgage(); // Toggles mortgaged field to opposite of what it was
    void toggleOwnership(); // Toggles owned field to opposite of what it was

    std::shared_ptr<PropertyConfig> getConfig() const; // Return shared_ptr to config
    void setConfig(const std::shared_ptr<PropertyConfig> config); // Sets config
};

#endif // OWNABLEPROPERTY_H
