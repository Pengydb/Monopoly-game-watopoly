#include "ownableproperty.h"
#include <string>

using namespace std;

OwnableProperty::OwnableProperty(string name, int loc, PropertyConfig& config) :
            Tile{name, loc}, config(config) {}


bool OwnableProperty::isOwned() const { return owned; }

bool OwnableProperty::isMortgage() const { return mortgaged; }

int OwnableProperty::getCost() const { return config.getCost(); }

int OwnableProperty::getFee() const { return config.getFee(0); }

string OwnableProperty::getGroup() const { return config.getGroup(); }


void OwnableProperty::toggleMortgage() { mortgaged = !(mortgaged); }

void OwnableProperty::toggleOwnership() { owned = !(owned); }

int OwnableProperty::getDepth() const { return 0; }

bool OwnableProperty::isPropertyEnhancement() const { return false; }

const PropertyConfig& OwnableProperty::getConfig() const { return config; }
