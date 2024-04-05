#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "subject.h"

class Player;
class Bank;

class Tile : public Subject {
  // Name of the tile
  std::string name;
  // location of the tile
  int location; 

public:
  // Constructor to initialize all necessary fields
  Tile(std::string name, int loc);
  // Default destructor
  virtual ~Tile() = default;
  // returns name field of Tile
  std::string getName() const;
  // returns the location field of Tile
  int getLocation() const;
  // This is a pure virtual method that must be implemented by derived classes.
  virtual void performAction(Player &p, Bank &b) = 0;
   
};

#endif // TILE_H
