#include "tile.h"
#include <string>
using namespace std;

Tile::Tile(string name) : name{name} {}

string Tile::getName() const { return name; }