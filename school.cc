#include "school.h"
#include <stdexcept>

School::School(const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<OwnableProperty>>& properties, int cards) {
    // Initialization logic here
}

School::~School() {
    // Cleanup logic here
}

void School::notify(Subject& s) {
    // Implementation here
}

int School::getDCTimsCups() const {
    return DCTimsCups;
}

void School::addDCTimsCups(int n) {
    if (DCTimsCups + n > 4 || DCTimsCups + n < 0) {
        throw std::invalid_argument("Invalid operation: Attempt to set DC Tims Cups outside of valid range.");
    }
    DCTimsCups += n;
}

void School::holdAuction(const std::string& propertyName) {
    // Implementation here
}

std::string School::getPropertyOwner(const std::string& propertyName) const {
    auto iter = propertyOwnership.find(propertyName);
    if (iter == propertyOwnership.end()) {
        throw std::invalid_argument("Property does not exist: " + propertyName);
    }
    return iter->second; 
}

std::weak_ptr<PropertyConfig> School::getPropertyConfig(const std::string& propertyName) {
    // Implementation here
    return std::weak_ptr<PropertyConfig>(); // Placeholder return
}

void School::addPropertyConfig(std::shared_ptr<PropertyConfig> config) {
    propertyConfigs[config->getName()] = config;
}

void School::transferProperty(const std::string& toPlayerName, const std::string& propertyName) {
    if (properties.find(propertyName) == properties.end()) {
        throw std::invalid_argument("Property does not exist: " + propertyName);
    }
    if (players.find(toPlayerName) == players.end()) {
        throw std::invalid_argument("Target player name does not exist: " + toPlayerName);
    }
    propertyOwnership[propertyName] = toPlayerName;
}

void School::transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount) {
    // Implementation here
}



int School::countBlocksOwnedBy(const std::string& playerName, const std::string& monopolyBlock) const {
    if (players.find(playerName) == players.end()) {
        throw std::invalid_argument("Target player name does not exist: " + playerName);
    }
    int count = 0;
    for (const auto& [propertyName, ownerName] : propertyOwnership) {
        if (ownerName == playerName) {
            auto iter = propertyConfigs.find(propertyName);
            if (iter != propertyConfigs.end() && iter->second->getGroup() == monopolyBlock) {
                ++count;
            }
        }
    }
    return count; // Placeholder return
}

int School::getLiquidAssets(const std::string& playerName) const {
    if (players.find(playerName) == players.end()) {
        throw std::invalid_argument("Target player name does not exist: " + playerName);
    }
    int assets = 0;
    assets += players.find(playerName)->second->getWallet();
    for (const auto& [propertyName, ownerName] : propertyOwnership) {
        if (ownerName == playerName) {
            auto iter = properties.find(propertyName);
            // check if academic building

            // if academic building check if mortgaged
            // if mortgaged nothing to add to assets
            // if not mortgaged add to liquid assets potential value for selling enhancments + mortgaging

            //if not academic building check if mortgaged
            // if mortgaged nothing to add to assets
            // if not mortgaged add to liquid assets potential value for mortgaging

        }
    }
   
    return assets; // Placeholder return
}

bool School::checkBankrupt(const std::string& playerName, int amount) const {
    // Implementation here
    return false; // Placeholder return
}

void School::buyImprovement(const std::string& propertyName) {
    // Implementation here
}

void School::sellImprovement(const std::string& propertyName) {
    // Implementation here
}

void School::mortgageProperty(const std::string& propertyName) {
    // Implementation here
}

void School::unmortgageProperty(const std::string& propertyName) {
    // Implementation here
}

void School::declareBankrupt(const std::string& playerName) {
    // Implementation here
}
