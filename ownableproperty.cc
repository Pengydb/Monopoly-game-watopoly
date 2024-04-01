#include "ownableproperty.h"
#include <string>

using namespace std;

OwnableProperty::OwnableProperty(string name, PropertyConfig& config) :
            Tile{name}, config(config) {}


bool OwnableProperty::isOwned() const { return owned; }

bool OwnableProperty::isMortgaged() const { return mortgaged; }

int OwnableProperty::getCost() const { return config.getCost(); }

int OwnableProperty::getFee() const { return config.getFee(0); }

string OwnableProperty::getGroup() const { return config.getGroup(); }

void OwnableProperty::toggleMortgage() { mortgaged = !(mortgaged); }

void OwnableProperty::toggleOwnership() { owned = !(owned); }

const PropertyConfig& OwnableProperty::getConfig() const { return config; }
