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
    int DCTimsCups; // total number of DCTims Cups that are owned by players
    
public:
    School(const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<OwnableProperty>>& properties, int cards);
    ~School();

    void notify(Subject& s);
    int getDCTimsCups() const; // returns DCTimsCups field
    void addDCTimsCups(int n); // adds n to DCTimsCups field

    void holdAuction(const std::string& propertyName);

    std::weak_ptr<Player> getPropertyOwner(const std::string& propertyName) const;
    void addPropertyOwner(const std::string& propertyName, const std::string& playerName);

    std::weak_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    void addPropertyConfig(std::shared_ptr<PropertyConfig> config);

    // Property transfer methods
    void transferProperty(const std::string& toPlayerName, const std::string& propertyName); // Player to Player
    void transferProperty(const std::string& propertyName); // Player to school
    void transferProperty(const std::string& propertyName, const std::string& toPlayerName); // School to player

    // Fund Transfer methods
    void transferFunds(const std::string& fromPlayerName, const std::string& toPlayerName, int amount);
    void transferFunds(const std::weak_ptr<Player>& fromPlayer, int amount); // Player to school
    void transferFunds(int amount, const std::weak_ptr<Player>& toPlayer); // school to Player

    // Player utility
    int countGymsOwnedBy(const std::string& playerName) const;
    int countResOwnedBy(const std::string& playerName) const;

    int getLiquidAssets(const std::string& playerName) const;
    bool checkBankrupt(const std::string& playerName, int amount) const;

    void buyImprovement(const std::string& propertyName);
    void sellImprovement(const std::string& propertyName);

    void mortgageProperty(const std::string& propertyName);
    void unmortgageProperty(const std::string& propertyName);

    void declareBankrupt(const std::string& playerName);
};  

#endif // SCHOOL_H
