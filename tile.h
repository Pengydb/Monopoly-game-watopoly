#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"
#include "player.h"
#include "bank.h"

class Tile : public Subject {
    std::string name;  // Name of the tile
    int location; // location of the tile

  public:
    Tile(std::string name, int loc); // Constructor for Tile

    std::string getName() const;   // returns name field of Tile
    int getLocation() const;
    virtual void performAction(Player &p, Bank &b) = 0; // pure virtual, no implimentation, for subclasses
    virtual int getCost() const = 0; // pure virtual, no implementation, for ownableproperties
    virtual ~Tile() = default; // Default destructor
};

#endif // TILE_H
