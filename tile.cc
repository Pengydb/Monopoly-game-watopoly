#include "tile.h"
#include <string>
using namespace std;

Tile::Tile(string name, int location) : name{name}, location{location} {}

string Tile::getName() const { return name; }
