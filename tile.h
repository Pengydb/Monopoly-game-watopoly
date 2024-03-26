#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"
using namespace std;

class Tile : public Subject {
    string name;  // Name of the tile
    int location; // Position of tile on the board

  public:
    Tile(string name, int loc); // Constructor for Tile

    int getLocation() const;  // returns name field of Tile
    string getName() const;   // returns location field of Tile
    
    virtual void performAction() = 0; // pure virtual, no implimentation, for subclasses
    virtual ~Tile(); // Default destructor
};


#endif