#include "school.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

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
    if (fromPlayerName == toPlayerName) { return; }
    if (fromPlayerName != "SCHOOL") {
        if (checkSufficientFunds(fromPlayerName, amount)) {
            players.find(fromPlayerName)->second->addWallet(-amount);
            if (toPlayerName != "SCHOOL") {
                players.find(toPlayerName)->second->addWallet(amount);
            }
        }
        else {

            // start bankruptcy procedure
        }
    }
    players.find(toPlayerName)->second->addWallet(amount);
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
        throw std::invalid_argument("Target player does not exist: " + playerName);
    }
    int assets = 0;
    assets += players.find(playerName)->second->getWallet();
    for (const auto& [propertyName, ownerName] : propertyOwnership) {
        if (ownerName == playerName) {
            auto iter = properties.find(propertyName);

            std::shared_ptr<OwnableProperty> property = iter->second;

            if(!property->isMortgaged()) {
                assets += property->getCost() * 0.5; // mortgage value is 50%

                auto academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);
                if (academicBuilding) {
                    assets += academicBuilding->getImpCount() * academicBuilding->getImpCost() * 0.5; // improvements sell for 50%
                }
            }
        }
    }
    return assets; 
}

bool School::checkSufficientFunds(const std::string& playerName, int amount) const {
    if (players.find(playerName) == players.end()) {
        throw std::invalid_argument("Target player does not exist: " + playerName);
    }
    std::shared_ptr<Player> player = players.find(playerName)->second;

    if (player->getWallet() < amount) {
        return true;
    }
    return false; // Placeholder return
}

void School::payDebts(const std::string& debotor, const std::string& creditor, int amount) {
    
    std::cout << debotor << ", you owe" << amount << ".\nDo you want to (1) attempt to liquidate assets or (2) declare bankruptcy?\nEnter 1 or 2: ";
    std::string in;
    int choice = 0;
    
    while (getline(std::cin, in)) {
        std::stringstream ss(in);
        if (ss >> choice) {
            if (choice == 1 || choice == 2) break;
        }
        std::cout << "Invalid input. Please enter 1 to liquidate assets or 2 to declare bankruptcy: ";
    }
    if (choice == 1) {

        while (!checkSufficientFunds(debotor, amount));
    }
}

void School::buyImprovement(const std::string& propertyName, const std::string& playerName) {

    if (playerName == "SCHOOL") {
        std::cout << "School cannot upgrade properties\n";
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
        throw std::invalid_argument("Target player does not exist: " + playerName);
    }

    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        throw std::invalid_argument("Property does not exist: " + propertyName);
    }

    std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(propertyIt->second);
    if (!academicBuilding) {
        std::cout << propertyName << " is not an Academic Building and cannot be improved.\n";
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "\n";
        return;
    }

    if(!academicBuilding->getMonopoly()) {
        std::cout << playerName << ", does not have a monopoly of type " << academicBuilding->getGroup() << "\n";
        return;
    }
    
    if (academicBuilding->getImpCount() == 5) {
        std::cout << propertyName << " is already at max improvement level.\n";
        return;
    }

    int upgradeCost = academicBuilding->getImpCost();
    if (!checkSufficientFunds(playerName, upgradeCost)) {
        std:: cout << playerName << ", lacks sufficient funds to improve " << propertyName << "\n";
        return;
    }

    transferFunds(playerName, "SCHOOL", upgradeCost);
    academicBuilding->addImps(1);
    std::cout << "Improvement purchased for " << propertyName << " by " << playerName << ".\n";
}

void School::sellImprovement(const std::string& propertyName, const std::string& playerName) {
    if (playerName == "SCHOOL") {
        std::cout << "School owned properties do not possess improvements to sell\n";
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
        throw std::invalid_argument("Target player does not exist: " + playerName);
    }

    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        throw std::invalid_argument("Property does not exist: " + propertyName);
    }

    std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(propertyIt->second);
    if (!academicBuilding) {
        std::cout << propertyName << " is not an Academic Building and lacks improvements to sell.\n";
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "\n";
        return;
    }

    if (academicBuilding->getImpCount() == 0) {
        std::cout << propertyName << " does not have improvements to sell.\n";
        return;
    }

    int upgradeCost = academicBuilding->getImpCost();
    int sellingValue = upgradeCost * 0.5;

    transferFunds("SCHOOL", playerName, sellingValue);
    academicBuilding->addImps(-1);
    std::cout << "Improvement sold for " << propertyName << " by " << playerName << ".\n";
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
