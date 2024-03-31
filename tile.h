#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"
#include "player.h"

class Tile : public Subject {
    std::string name;  // Name of the tile
    int location; // Position of tile on the board

  public:
    Tile(std::string name, int loc); // Constructor for Tile

    int getLocation() const;  // returns name field of Tile
    std::string getName() const;   // returns location field of Tile
    
    virtual void performAction(Player &p) = 0; // pure virtual, no implimentation, for subclasses
    virtual ~Tile() = default; // Default destructor
};

#endif // TILE_H
