#include "bank.h"
#include "player.h"
#include "ownableproperty.h"
#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "tile.h"
#include "textdisplay.h"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>


Bank::Bank() : DCTimsCups(0) {
    players["BANK"] = nullptr;
}

int Bank::getDCTimsCups() const {
    return DCTimsCups;
}

void Bank::addDCTimsCups(int n) {
    if (DCTimsCups + n > 4 || DCTimsCups + n < 0) {
        throw std::invalid_argument("Invalid operation: Attempt to set DC Tims Cups outside of valid range.");
    }
    DCTimsCups += n;
}

std::string Bank::getPropertyOwner(const std::string& propertyName) const {
    auto iter = propertyOwnership.find(propertyName);
    if (iter == propertyOwnership.end()) {
        std::cout << "Property does not exist: " + propertyName << "." << std::endl;
        return "";
    }
    return iter->second; 
}

std::shared_ptr<PropertyConfig> Bank::getPropertyConfig(const std::string& propertyName) {
    // Implementation here
    return propertyConfigs[propertyName];
}

std::shared_ptr<OwnableProperty> Bank::getProperty(const std::string& propertyName) {
    return properties[propertyName];
}

void Bank::addPropertyOwner(const std::string& propertyName, const std::string& playerName) {
    if (properties.find(propertyName) == properties.end()) {
        std::cout << "Property does not exist: " + propertyName << "." << std::endl;
        return;
    }
    if (players.find(playerName) == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
        return;
    }
    propertyOwnership[propertyName] = playerName;
}

void Bank::addPropertyConfig(std::shared_ptr<PropertyConfig> config) {
    propertyConfigs[config->getName()] = config;
}

bool Bank::transferProperty(const std::string& toPlayerName, const std::string& propertyName) {
    if (properties.find(propertyName) == properties.end()) {
        std::cout << "Property does not exist: " + propertyName << "." << std::endl;
        return false;
    }
    if (players.find(toPlayerName) == players.end()) {
        std::cout << "Target player does not exist: " + toPlayerName << "." << std::endl;
        return false;
    }

    std::string currentOwner = propertyOwnership[propertyName];

    if (currentOwner == toPlayerName) {
        std::cout << "Cannot transfer property from self to self." << std::endl;
        return false;
    }

    std::shared_ptr<PropertyConfig> propertyConfig = propertyConfigs[propertyName];
    propertyOwnership[propertyName] = toPlayerName;
    std::shared_ptr<OwnableProperty> property = properties[propertyName];

    if (property->isMortgaged()) {
        int mortgageTransferFee = property->getCost() * 0.1;
        std::cout << toPlayerName <<" you are receiving " << propertyName << " which is currently a mortgaged property, as a result you will be"
                                                                             " chared a fee of $" << mortgageTransferFee << "." << std::endl;
        transferFunds(toPlayerName, "BANK", mortgageTransferFee);
        std::cout << toPlayerName << " do you wish to unmortgage " << propertyName << " now? (Enter: (yes/no)" << std::endl;

        std::string response;
        while (true) {
            std::cin >> response;
            std::transform(response.begin(), response.end(), response.begin(), [](unsigned char c){ return std::tolower(c); });
            if (response == "yes") {
            int unmortgageCost = property->getCost() * 0.5;
            std::cout << "Unmortgaging " << propertyName << " will cost $" << unmortgageCost << "." << std::endl;
            transferFunds(toPlayerName, "BANK", unmortgageCost);
            property->toggleMortgage();
            std::cout << propertyName << " has been unmortgaged." << std::endl;
            break; 
            } else if (response == "no") {
                std::cout << toPlayerName << ", you have chosen not to unmortgage " << propertyName << " now. Remember, unmortgaging later will cost"
                                                                                                       " 60% of the original cost." << std::endl;
                break; 
            } else {
                std::cout << "Invalid response. Please answer 'yes' or 'no':" << std::endl;
            }
        }
    }

    if (propertyConfig->getGroup() == "Gym") {
            if (toPlayerName != "BANK") {
                players[toPlayerName]->addGyms(1);
            }
            if (currentOwner != "BANK") {
                players[currentOwner]->addGyms(-1);
            }
    } else if (propertyConfig->getGroup() == "Residence") {
            if (toPlayerName != "BANK") {
                players[toPlayerName]->addRes(1);
            }
            if (currentOwner != "BANK") {
                players[currentOwner]->addRes(-1);
            }
    } else {
        updateMonopoly(propertyConfig->getGroup());
    }

    std::cout << propertyName << " successfully transfered from " << currentOwner << " to " << toPlayerName << "." << std::endl;
    return true;
}

bool Bank::transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount) {
    if (fromPlayerName == toPlayerName) { return false; }
    if (fromPlayerName != "BANK") {
        if (checkSufficientFunds(fromPlayerName, amount)) {
            players.find(fromPlayerName)->second->addWallet(-amount);
            if (toPlayerName != "BANK") {
                players.find(toPlayerName)->second->addWallet(amount);
            }
            std:: cout << "Sucessfully transfered $" << amount << " from " << fromPlayerName << " to " << toPlayerName << "." << std::endl;
            return true;
        }
        else {
            std:: cout << fromPlayerName << " lacks sufficient funds to transfer." << std::endl;
            return false;
        }
    }
    players.find(toPlayerName)->second->addWallet(amount);
    std:: cout << "Sucessfully transfeer $" << amount << " from " << fromPlayerName << " to " << toPlayerName << "." << std::endl;
    return true;
}

void Bank::updateMonopoly(const std::string& monopolyGroup) {
    std::string monopolyOwner = "";
    bool isMonopoly = true;
    std::vector<std::shared_ptr<AcademicBuilding>> groupProperties;
    for(const auto& [propertyName, proprtyConfig] : propertyConfigs) {
        if (proprtyConfig->getGroup() == monopolyGroup) {
            std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(properties[propertyName]);
            if (academicBuilding) {
                groupProperties.emplace_back(academicBuilding);
                auto& propertyOwner = propertyOwnership[propertyName];

                if (monopolyOwner.empty() && propertyOwner != "BANK") {
                    monopolyOwner = propertyOwner;
                } else if (propertyOwner == "BANK" || propertyOwner != monopolyOwner) {
                    isMonopoly = false;
                }
            }
        }
    }
    for (const auto& property: groupProperties) {
        property->setMonopoly(isMonopoly);
    }
}

void Bank::seizeAssets(const std::string& debtor, const std::string& creditor) {
    auto debtorIt = players.find(debtor);
    if (debtorIt == players.end()) {
        std::cout << "Debtor does not exist: " << debtor << "." << std::endl;
        return;
    }
    if (debtorIt->first == "BANK") {
        std::cout << "Cannot seize assets from the Bank." << std::endl;
        return;
    }
    auto creditorIt = players.find(creditor);
    if (creditorIt == players.end()) {
        std::cout << "Creditor does not exist: " << creditor << "." << std::endl;
        return;
    }

    std::vector<std::string> propertiesSeized;
    int cashSeized = players[debtor]->getWallet();

    transferFunds(debtor, creditor, cashSeized);

    creditorIt->second->addTimsCups(debtorIt->second->getTimsCups());
    debtorIt->second->addTimsCups(-debtorIt->second->getTimsCups());

    for (auto& [propertyName, owner] : propertyOwnership) {
        if (owner == debtor) {
            std::shared_ptr<OwnableProperty> property = properties[propertyName];
            if (creditor == "BANK") {
                if (property->isMortgaged()) {
                    property->toggleMortgage();
                }
                std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(properties[propertyName]);
                if (academicBuilding) {
                    academicBuilding->addImps(-academicBuilding->getImpCount());
                    academicBuilding->setMonopoly(false);
                }
                property->toggleOwnership();
                propertyOwnership[propertyName] = "BANK";
                holdAuction(propertyName);
            }
        } else {
            transferProperty(debtor, creditor);
        }
    }

    std::cout << "Sucessfully transferred all assets from " << debtor << " to " << creditor << "." << std::endl;
}

int Bank::countBlocksOwnedBy(const std::string& playerName, const std::string& monopolyBlock) const {
    if (players.find(playerName) == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
        return -1;
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
    return count; 
}

void Bank::printAssets(const std::string& playerName) const {
    if (players.find(playerName) == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
        return;
    }

    std::shared_ptr<Player> player = players.find(playerName)->second;
    std::cout << playerName << "cash: $" << player->getWallet() << "tims cups: " << player->getTimsCups() << std::endl;
    for (const auto& [propetyName, ownerName] : propertyOwnership) {
        if (ownerName == playerName) {
            std::shared_ptr<OwnableProperty> property = properties.find(propetyName)->second;
            int improvements = 0;
            if (property->isMortgaged()) {
                improvements = -1;
            } else {
                auto academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(property);
                if (academicBuilding) {
                    improvements = academicBuilding->getImpCount();
                }
            }

            std:: cout << propetyName << " " << improvements << std::endl;
        }
    }
}

int Bank::getLiquidAssets(const std::string& playerName) const {
    if (players.find(playerName) == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
        return -1;
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

bool Bank::checkSufficientFunds(const std::string& playerName, int amount) const {
    if (players.find(playerName) == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
        return false;
    }
    std::shared_ptr<Player> player = players.find(playerName)->second;

    if (player->getWallet() < amount) {
        return true;
    }
    return false; 
}

void Bank::buyImprovement(const std::string& propertyName, const std::string& playerName) {

    if (playerName == "BANK") {
        std::cout << "Bank cannot upgrade properties." << std::endl;
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
       std::cout << "Target player does not exist: " + playerName << "." << std::endl;
    }

    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        std::cout << "Property does not exist: " + propertyName << "." << std::endl;
    }

    std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(propertyIt->second);
    if (!academicBuilding) {
        std::cout << propertyName << " is not an Academic Building and cannot be improved." << std::endl;
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "." << std::endl;
        return;
    }

    if(!academicBuilding->getMonopoly()) {
        std::cout << playerName << ", does not have a monopoly of type " << academicBuilding->getGroup() << "." << std::endl;
        return;
    }
    
    if (academicBuilding->getImpCount() == 5) {
        std::cout << propertyName << " is already at max improvement level." << std::endl;
        return;
    }

    int upgradeCost = academicBuilding->getImpCost();
    if (!checkSufficientFunds(playerName, upgradeCost)) {
        std:: cout << playerName << ", lacks sufficient funds to improve " << propertyName << "." << std::endl;
        return;
    }

    transferFunds(playerName, "BANK", upgradeCost);
    academicBuilding->addImps(1);
    std::cout << "Improvement for " << propertyName << " purchased by " << playerName << " for $" << upgradeCost << "." << std::endl;
}

void Bank::sellImprovement(const std::string& propertyName, const std::string& playerName) {
    if (playerName == "BANK") {
        std::cout << "Bank owned properties do not possess improvements to sell." << std::endl;
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
        std::cout << "Target player does not exist: " + playerName << "." << std::endl;
    }

    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        std::cout << "Property does not exist: " + propertyName << "." << std::endl;
    }

    std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(propertyIt->second);
    if (!academicBuilding) {
        std::cout << propertyName << " is not an Academic Building and lacks improvements to sell." << std::endl;
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "." << std::endl;
        return;
    }

    if (academicBuilding->getImpCount() == 0) {
        std::cout << propertyName << " does not have improvements to sell." << std::endl;
        return;
    }

    int upgradeCost = academicBuilding->getImpCost();
    int sellingValue = upgradeCost * 0.5;

    transferFunds("BANK", playerName, sellingValue);
    academicBuilding->addImps(-1);
    std::cout << "Improvement for " << propertyName << " sold by " << playerName << " for $" << sellingValue << "." << std::endl;
}

void Bank::mortgageProperty(const std::string& propertyName, const std::string& playerName) {
    if (playerName == "BANK") {
        std::cout << "Bank cannot mortgage a property" << std::endl;
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
        std::cout << "Player does not exist: " << playerName << std::endl;
        return;
    }
    
    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        std::cout << "Property does not exist: " << propertyName << std::endl;
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "." << std::endl;
        return;   
    }

    std::shared_ptr<AcademicBuilding> academicBuilding = std::dynamic_pointer_cast<AcademicBuilding>(propertyIt->second);
    if (academicBuilding && academicBuilding->getImpCount() > 0) {
        std::cout << propertyName << " cannot be mortgaged because it has improvements. Must sell improvements first before mortaging." << std::endl;
        return;
    }

    if (propertyIt->second->isMortgaged()) {
        std::cout << propertyName << " is already mortaged." << std::endl;
        return;
    }

    int mortgageValue = propertyIt->second->getCost() * 0.5;
    transferFunds("BANK", playerName, mortgageValue);
    propertyIt->second->toggleMortgage();

    std::cout << playerName << " has mortgaged " << propertyName << " for $" << mortgageValue << "." << std::endl;
}


void Bank::unmortgageProperty(const std::string& propertyName, const std::string& playerName) {
    if (playerName == "BANK") {
        std::cout << "Bank cannot mortgage a property" << std::endl;
        return;
    }

    auto playerIt = players.find(playerName);
    if (playerIt == players.end()) {
        std::cout << "Player does not exist: " << playerName << std::endl;
        return;
    }
    
    auto propertyIt = properties.find(propertyName);
     if (propertyIt == properties.end()) {
        std::cout << "Property does not exist: " << propertyName << std::endl;
        return;
    }

    if (playerName != propertyOwnership[propertyName]) {
        std:: cout << playerName << ", does not own " << propertyName << "." << std::endl;
        return;   
    }

    if (!propertyIt->second->isMortgaged()) {
        std::cout << propertyName << " is not mortgaged and cannot be unmortgaged." << std::endl;
        return;
    }    

    int unmortgageCost = propertyIt->second->getCost() * 0.6;

    if (!checkSufficientFunds(playerName, unmortgageCost)) {
        std::cout << playerName << ", lacks sufficient funds to unmortgage " << propertyName << "." << std::endl; 
        std::cout << "You have $" << players[playerName] ->getWallet() << "." << std::endl;
        std::cout << "It costs $" << unmortgageCost << "." << std::endl;
        return;
    }

    transferFunds(playerName, "BANK", unmortgageCost);
    propertyIt->second->toggleMortgage();

    std::cout << playerName << " has paid $" << unmortgageCost << " to unmortgage " << propertyName << "." << std::endl;
}

void Bank::removePlayer(const std::string& playerName) {
    auto it = players.find(playerName); // Checks if player is in map, if not it == player.end()
    if (it != players.end()) {
        std::cout << playerName << " is not a player" << std::endl;
    } else {
        this->addDCTimsCups( -(players[playerName]->getTimsCups()) ); // Updates total owned Tims Cups 
        players.erase(playerName);
        std::cout << playerName << " has gone bankrupt and can no longer continue" << std::endl;
    }
}

void Bank::initBank(std::vector<std::shared_ptr<Player>> &p) {
    for (const auto &player : p) {
        players[player->getName()] = player;
        addDCTimsCups(player->getTimsCups());
    }
}

void Bank::initBank(std::vector<std::shared_ptr<Tile>> &buildings) {
    std::vector<std::shared_ptr<OwnableProperty>> props;
    for (const auto &tile : buildings) {
        if (std::shared_ptr<OwnableProperty> ownable = std::dynamic_pointer_cast<OwnableProperty>(tile)) {
            props.push_back(ownable);
        }
    }

    for (const auto &property : props) {
        properties[property->getName()] = property;
        propertyOwnership[property->getName()] = "BANK";
    }
}

void Bank::initConfigs(const std::string& configFile) {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << configFile << std::endl;
    }
    std::string csvLine;
    std::getline(file, csvLine);
    while(std::getline(file, csvLine)) {
        auto config = PropertyConfig::fromCSV(csvLine);
        std::string propertyName = config.getName();
        propertyConfigs[propertyName] = std::make_shared<PropertyConfig>(config);
    }
    for (auto& [propertyName, property] : properties) {
        auto configIt = propertyConfigs.find(propertyName);
        if (configIt != propertyConfigs.end()) {
            property->setConfig(configIt->second);
        } else {
            std::cout << "Warning: No configuration found for property " << propertyName << "." << std::endl;
        }

    }

    file.close();
}

void Bank::holdAuction(const std::string &propertyName){
    std::vector<std::string> names;
    for (const auto &pair : players)
    {
        names.push_back(pair.first); // To construct the names vector to store the names of the players
    }
    int highestBid = 1; // Starting bid
    std::string highestBidder = ""; // To store the winning bidder
    while(true){
        if (names.size() == 1){
            highestBidder = names[0];
            bool check = checkSufficientFunds(highestBidder, highestBid);
            if (check){
                std::cout << "Congratulations! " << highestBidder << " has won the auction for $" << highestBid << std::endl;
                transferFunds(highestBidder, "BANK", highestBid);
                transferProperty("BANK", highestBidder);
                std::cout << "The transfer has been complete" << std::endl;
            }
            else {
                std::cout << "No one has won the auction so the property will remain with the Bank" << std::endl;
            }
            
        }
        std::string bidder = ""; // Current bidder
        std::cout << "Players: ";
        for (const auto& name : names){
            std::cout << name << " ";
        }
        std:: cout << "." << std::endl; // To output the list of players currently in the auction

        std::cout << "Please enter the name of the bidder" << std::endl;
        std::getline(std::cin, bidder); // To enter the name of the bidder

        bool match = false;
        for (const auto &name : names)
        {
            if (bidder == name){
                match = true; // check if it is a valid player
            }
        }
        if (!match){ // If not the prompted to enter the name again
            throw std::invalid_argument("Please enter a valid player");
            continue;
        }
        while (true){
            std::string input;
            int tempBid = 0; // Stores Current bid
            std::cout << "Please enter a bid greater than $" << highestBid << " (or enter withdraw to leave the auction)" << std::endl;
            std::getline(std::cin, input);
            std::istringstream iss(input);
            if (iss >> tempBid){ // Checks whether the input entered is a number or a string
                if (tempBid > highestBid){ // If it is a number then checking if it is a valid bid
                    bool check = checkSufficientFunds(highestBidder, highestBid); // Checking if the player can pay the bid
                    if (check){
                        highestBid = tempBid;
                        highestBidder = bidder; // If yes then it is the current winning bid and bidder
                        std::cout << "The current highest bidder is " << highestBidder << "for $" << highestBid << std::endl;
                        break;
                    }
                    else {
                        std::cout << "You have insufficient funds to cover this bid, please enter a valid bid or withdraw" << std::endl;
                        continue;
                    }
                }
            }
            else { // If it is not a bid then checking if it is withdraw
                std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "withdraw"){ // If it is withdraw then the name is removed from the player list
                    if (bidder == highestBidder){
                        std::cout << "You cannot leave the auction as you are currently the highest bidder" << std::endl;
                        break;
                    }
                    auto it = std::find(names.begin(), names.end(), bidder);
                        names.erase(it);
                    std::cout << bidder << " has withdrawn from the auction" << std::endl;
                    break;
                }
            }
            std::cout << "Please enter a valid bid greater than $" << highestBid << " or withdraw" << std::endl;
        }
        
        
    }
}


int Bank::countImprovements(const std::string& group) const {
    int imps = 0;
    int index = 0;
    int found = false;
    for (auto p = properties.begin(); p != properties.end(); ++p) {
        if (p->second->getGroup() == group) {
            std::shared_ptr<AcademicBuilding> ab = std::dynamic_pointer_cast<AcademicBuilding>(p->second);
            imps += ab->getImpCount();
            found = true;
            index++;
        }
        if (found) index++;
        if (index == 4) break;
    }
    return imps;
}

