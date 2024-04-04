#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"

class Player;
class Bank;

class Tile : public Subject {
    std::string name;  // Name of the tile
    int location; // location of the tile

  public:
    Tile(std::string name, int loc); // Constructor for Tile
    virtual ~Tile() = default; // Default destructor
    std::string getName() const;   // returns name field of Tile
    int getLocation() const;
    virtual void performAction(Player &p, Bank &b) = 0; // pure virtual, no implimentation, for subclasses
    virtual int getCost() const = 0; // pure virtual, no implementation, for ownableproperties
    
};

#endif // TILE_H
