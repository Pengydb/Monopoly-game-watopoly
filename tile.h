#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"
#include "player.h"

class Tile : public Subject {
    std::string name;  // Name of the tile

  public:
    Tile(std::string name); // Constructor for Tile

    std::string getName() const;   // returns location field of Tile
    
    virtual void performAction(Player &p) = 0; // pure virtual, no implimentation, for subclasses
    virtual ~Tile() = default; // Default destructor
};

#endif // TILE_H
