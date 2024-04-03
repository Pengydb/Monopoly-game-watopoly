#include "tile.h"
#include <string>

Tile::Tile(std::string name, int loc) : name{name}, location{loc} {}

std::string Tile::getName() const { return name; }
int Tile::getLocation() const { return location; }
