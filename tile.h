#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"
#include "player.h"
#include "school.h"

class Tile : public Subject {
    std::string name;  // Name of the tile
    int location; // Location of the tile

  public:
    Tile(std::string name, int location); // Constructor for Tile

    std::string getName() const;   // returns name field of Tile

    int getLocation() const;  // returns location field of Tile

    virtual void performAction(Player &p, School &s) = 0; // pure virtual, no implimentation, for subclasses
    virtual ~Tile() = default; // Default destructor
};

#endif // TILE_H
