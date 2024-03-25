#ifndef _OWNABLEPROPERTY_H_
#define _OWNABLEPROPERTY_H_

#include "tile.h"

class OwnableProperty : public Tile {
    int cost;        // Cost to buy property
    int fee;         // Fee charged if player lands on already owned property
    bool owned;      // True if property is owned, false otherwise
    bool mortgaged;  // True if property is mortgaged, false otherwise

  public:
    OwnableProperty(int cost, int fee, bool ow, bool mort);
    // Performs action when player lands on an ownable property 
    // 1) Prompts player to buy if unowned.
    //    -  If player can't afford or doens't buy, property goes up for auction
    // 2) Charges player a fee if owned and not mortgaged
    //    -  If player can't afford to pay fee, then they can declare bankrupcy, 
    // try selling any of their assets, or try and trade (if they have property)
    virtual void performAction() = 0; 

    bool isOwned() const; // Returns owned field
    int getCost() const; // Returns cost field
    int getFee() const; // Returns fee field
    bool getMortgage() const; // returns mortgage field

    void setCost(const int c); // sets cost field to c
    void setFee(const int f); // sets fee field to f
    void setMortgage(const bool b); // sets mortgage field to b
};

#endif