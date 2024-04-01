#include "ownableproperty.h"
#include <string>

using namespace std;

OwnableProperty::OwnableProperty(PropertyConfig& config) :
            Tile{config.getName()}, config(config) {}

int OwnableProperty::getCost() const { return config.getCost(); }

int OwnableProperty::getFee() const { return config.getFee(0); }

string OwnableProperty::getGroup() const { return config.getGroup(); }

int OwnableProperty::getDepth() const { return 0; }

bool OwnableProperty::isPropertyEnhancement() const { return false; }

const PropertyConfig& OwnableProperty::getConfig() const { return config; }
