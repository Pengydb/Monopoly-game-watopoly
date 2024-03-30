#include "tile.h"
#include <string>
using namespace std;

Tile::Tile(string name, int loc) : name{name}, location{loc} {}

int Tile::getLocation() const { return location; }

string Tile::getName() const { return name; }