#ifndef __SCHOOL_H_
#define __SCHOOL_H_

#include "observer.h"
#include "player.h"
#include "ownableproperty.h"
#include "academicbuilding.h"
#include "propertyconfig.h"
#include <map>
#include <memory>
#include <string>

class School: public Observer {
private:
    std::map<std::string, std::shared_ptr<PropertyConfig>> propertyConfigs; // Property configs
    std::map<std::string, std::shared_ptr<Player>> players; // Maps player name to player
    std::map<std::string, std::shared_ptr<OwnableProperty>> properties; // Mpas property name to property
    std::map<std::string, std::string> propertyOwnership; // maps property name to player name
    int DCTimsCups; // total number of DCTims Cups that are owned by players (get out of jail)
    
public:
    School(const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<OwnableProperty>>& properties, int cards);
    ~School();

    void notify(Subject& s);

     // Returns DCTimsCups field
    int getDCTimsCups() const;

    // Adds n to DCTimsCups field. Will not allow to go above 4 or below 0 (throws invalid_argument).
    void addDCTimsCups(int n); 

    void holdAuction(const std::string& propertyName);

    std::string getPropertyOwner(const std::string& propertyName) const;
    void addPropertyOwner(const std::string& propertyName, const std::string& playerName);

    std::weak_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    void addPropertyConfig(std::shared_ptr<PropertyConfig> config);

    // Transfers property from one player to another
    void transferProperty(const std::string& toPlayerName, const std::string& propertyName); //  (school has name SCHOOL)

    // Transfers funds from fromPlayerName to toPlayerName, will check for bankruptucy and seize assets if necessary. (Use SCHOOL as name school)
    void transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount);

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

    void declareBankrupt(const std::string& playerName);
};  

#endif // SCHOOL_H
