#ifndef __BANK_H_
#define __BANK_H_


#include "propertyconfig.h"
#include <map>
#include <memory>
#include <string>

class Tile;
class Player;
class OwnableProperty;
class Bank {
private:
    // Maps property name to Property configs
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
    // Constructor that adds the bank as one of the players
    Bank();
    
    // Default destructor 
    ~Bank() = default;

     // Returns DCTimsCups field
    int getDCTimsCups() const;

    // Adds n to DCTimsCups field. Will not allow to go above 4 or below 0 (throws invalid_argument).
    void addDCTimsCups(int n);

    // Initializes the players
    void initBank(std::vector<std::shared_ptr<Player>> &p);
    // Initializes the properties, and propertyOwnership maps
    void initBank(std::vector<std::shared_ptr<Tile>> &buildings);
    
    // Hold the auction process
    void holdAuction(const std::string& propertyName);
    // Returns the owner of the property
    std::string getPropertyOwner(const std::string& propertyName) const;

    // Returns pointer to player
    std::shared_ptr<Player> getPlayer(const std::string& playerName) const;


    // Changes the owner of the property
    void addPropertyOwner(const std::string& propertyName, const std::string& playerName);

    // Initilizes and updates ownable property config map in bank from filename csv, subsequently updates each property's config pointer
    void initConfigs(const std::string &configFile);
    // Returns the smart pointer to the property, given its name
    std::shared_ptr<OwnableProperty> getProperty(const std::string& propertyName);
    // Returns the smart pointer to the property's configuration, given its name
    std::shared_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    // Adds a configuration to the propertyConfigs map
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
    // Purchases an improvement for the player
    void buyImprovement(const std::string& propertyName, const std::string& playerName);
    // Sells an improvement for the player
    void sellImprovement(const std::string& propertyName, const std::string& playerName);
    // Mortgages the property for the player
    void mortgageProperty(const std::string& propertyName, const std::string& playerName);
    // Unmortgages the property for the player
    void unmortgageProperty(const std::string& propertyName, const std::string& playerName);

    // Removes player from bank's tracking, to be used after a player has declared bankruptcy and all their assets have been transferred
    void removePlayer(const std::string& playerName);

    // Counts the number of improvements that are on a certain group
    // Uses location (loc) as a starting point to count
    // Assumes group represents a monopoly block
    int countImprovements(const std::string& group) const;

};  

#endif // BANK_H
