#include "ownableproperty.h"
#include <string>

OwnableProperty::OwnableProperty(std::string name, int loc, std::shared_ptr<PropertyConfig> config, bool owned, bool mortgaged) : 
Tile{name, loc}, owned{owned}, mortgaged{mortgaged}, config(config) {}

bool OwnableProperty::isOwned() const { return owned; }

bool OwnableProperty::isMortgaged() const { return mortgaged; }

int OwnableProperty::getCost() const { return config->getCost(); }

int OwnableProperty::getFee() const { return config->getFee(0); }

std::string OwnableProperty::getGroup() const { return config->getGroup(); }

void OwnableProperty::toggleMortgage() { mortgaged = !(mortgaged); }

void OwnableProperty::toggleOwnership() { owned = !(owned); }

std::shared_ptr<PropertyConfig> OwnableProperty::getConfig() const { return config; }

void OwnableProperty::setConfig(std::shared_ptr<PropertyConfig> newConfig) {
        config = newConfig;
 }
