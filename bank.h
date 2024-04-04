#ifndef __BANK_H_
#define __BANK_H_

#include "player.h"
#include "ownableproperty.h"
#include "academicbuilding.h"
#include "propertyconfig.h"
#include <map>
#include <memory>
#include <string>

class Bank {
private:
    // Property configs
    std::map<std::string, std::shared_ptr<PropertyConfig>> propertyConfigs; 
    // Maps player name to player
    std::map<std::string, std::shared_ptr<Player>> players; 
    // Maps property name to property
    std::map<std::string, std::shared_ptr<OwnableProperty>> properties; 
    // Maps property name to player name
    std::map<std::string, std::string> propertyOwnership;
    // total number of DCTims Cups that are owned by players (get out of jail)
    int DCTimsCups; 
    
public:
    Bank();
    
    // Default destructor 
    ~Bank() = default;

     // Returns DCTimsCups field
    int getDCTimsCups() const;

    // Adds n to DCTimsCups field. Will not allow to go above 4 or below 0 (throws invalid_argument).
    void addDCTimsCups(int n);

    // Initializes the players, properties, and propertyOwnership maps
    void initBank(std::vector<std::shared_ptr<Player>> &p, std::vector<std::shared_ptr<OwnableProperty>> &props);

    void holdAuction(const std::string& propertyName);

    std::string getPropertyOwner(const std::string& propertyName) const;
    void addPropertyOwner(const std::string& propertyName, const std::string& playerName);

    void initilizePropertyConfigs(const std::string &filename);

    std::weak_ptr<OwnableProperty> getProperty(const std::string& propertyName);

    std::weak_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    
    void addPropertyConfig(std::shared_ptr<PropertyConfig> config);

    /* Transfers property from one player to another returns true if successfull, charges receiver a fee if the property is mortgaged and gives 
    option to unmortgage now or later. Returns true if successfull with a message to stdout and false with relevent message if failed*/
    bool transferProperty(const std::string& toPlayerName, const std::string& propertyName); //  (bank has name BANK)

    // Updates monopoly status for all properties within group
    void updateMonopoly(const std::string& monopolyGroup);

    // Transfers all assets (cash, timcups, properties) from debtor to creditor, if creditor is the bank an auction is held for each property. 
    void seizeAssets(const std::string& debtor, const std::string& creditor);

    // Transfers funds from fromPlayerName to toPlayerName, will not work if fromPlayer lacks sufficient funds and a message will be displayed
    bool transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount);

    // Counts number of properities of given group that the player owns
    int countBlocksOwnedBy(const std::string& playerName, const std::string& monopolyBlock) const;

    // Print's the player's assets
    void printAssets(const std::string& playerName) const;

    // Calculates player's total liquid assets from cash and mortgaging all properties and/or selling improvements
    int getLiquidAssets(const std::string& playerName) const;

    // Checks if player has solvency to pay amount
    bool checkSufficientFunds(const std::string& playerName, int amount) const;

    void buyImprovement(const std::string& propertyName, const std::string& playerName);
    void sellImprovement(const std::string& propertyName, const std::string& playerName);

    void mortgageProperty(const std::string& propertyName, const std::string& playerName);
    void unmortgageProperty(const std::string& propertyName, const std::string& playerName);

    // Removes player from bank's tracking, to be used after a player has declared bankruptcy and all their assets have been transferred
    void removePlayer(const std::string& playerName);

    // Counts the number of improvements that are on a certain group
    // Uses location (loc) as a starting point to count
    // Assumes group represents a monopoly block
    int countImprovements(const std::string& group) const;

};  

#endif // BANK_H
