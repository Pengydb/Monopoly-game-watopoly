#ifndef __SCHOOL_H_
#define __SCHOOL_H_

#include "player.h"
#include "ownableproperty.h"
#include "academicbuilding.h"
#include "propertyconfig.h"
#include <map>
#include <memory>
#include <string>

class School {
private:
    std::map<std::string, std::shared_ptr<PropertyConfig>> propertyConfigs; // Property configs
    std::map<std::string, std::shared_ptr<Player>> players; // Maps player name to player
    std::map<std::string, std::shared_ptr<OwnableProperty>> properties; // Mpas property name to property
    std::map<std::string, std::string> propertyOwnership; // maps property name to player name
    int DCTimsCups; // total number of DCTims Cups that are owned by players (get out of jail)
    
public:
    School();
    
    ~School() = default;

    void notify(Subject& s);

     // Returns DCTimsCups field
    int getDCTimsCups() const;

    // Adds n to DCTimsCups field. Will not allow to go above 4 or below 0 (throws invalid_argument).
    void addDCTimsCups(int n);

    // Initializes the players, properties, and propertyOwnership maps
    void initSchool(std::vector<std::shared_ptr<Player>> &p, std::vector<std::shared_ptr<OwnableProperty>> &props);

    void holdAuction(const std::string& propertyName);

    std::string getPropertyOwner(const std::string& propertyName) const;
    void addPropertyOwner(const std::string& propertyName, const std::string& playerName);

    void initilizePropertyConfigs(const std::string &filename);


    std::weak_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    void addPropertyConfig(std::shared_ptr<PropertyConfig> config);

    // Transfers property from one player to another
    void transferProperty(const std::string& toPlayerName, const std::string& propertyName); //  (school has name SCHOOL)

    // Updates monopoly status for all properties within group
    void updateMonopoly(const std::string& monopolyGroup);

    // transfers all assets from debtor to creditor, if creditor is school holds auction for each property
    void seizeAssets(const std::string& debotor, const std::string& creditor);


    // Transfers funds from fromPlayerName to toPlayerName, will not work if fromPlayer lacks sufficient funds and a message will be displayed
    bool transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount);

    void payDebts(const std::string& debotor, const std::string& creditor, int amount);
    // Counts number of properities of given group that the player owns
    int countBlocksOwnedBy(const std::string& playerName, const std::string& monopolyBlock) const;

    // Calculates player's total liquid assets from cash and mortgaging all properties and/or selling improvements
    int getLiquidAssets(const std::string& playerName) const;

    // Checks if player has solvency to pay amount
    bool checkSufficientFunds(const std::string& playerName, int amount) const;

    void buyImprovement(const std::string& propertyName, const std::string& playerName);
    void sellImprovement(const std::string& propertyName, const std::string& playerName);

    void mortgageProperty(const std::string& propertyName, const std::string& playerName);
    void unmortgageProperty(const std::string& propertyName, const std::string& playerName);

    // Removes player from school's tracking, to be used after a player has declared bankruptcy and all their assets have been transferred
    void removePlayer(const std::string& playerName);
};  

#endif // SCHOOL_H
