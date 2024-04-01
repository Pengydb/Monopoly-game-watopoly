#ifndef __SCHOOL_H_
#define __SCHOOL_H_

#include "observer.h"
#include "player.h"
#include "ownableproperty.h"
#include "propertyconfig.h"
#include <map>
#include <memory>
#include <string>

class School: public Observer {
private:
    std::map<std::weak_ptr<OwnableProperty>, std::weak_ptr<Player>, std::owner_less<std::weak_ptr<OwnableProperty>>> propertyOwnership;
    std::map<std::string, std::shared_ptr<PropertyConfig>> propertyConfigs;
    int DCTimsCards; // total number of DCTims Cards that are owned by players

public:
    School(const std::vector<std::shared_ptr<Player>>& players, const std::vector<std::shared_ptr<OwnableProperty>>& properties, int cards);
    ~School();

    void notify(Subject& s);
    void getDCTimsCards() const; // returns DCTimsCards field

    void holdAuction(const std::weak_ptr<OwnableProperty>& property);

    std::weak_ptr<Player> getPropertyOwner(const std::weak_ptr<OwnableProperty>& property) const;
    void addPropertyOwner(const std::weak_ptr<OwnableProperty>& property, const std::weak_ptr<Player>& player);

    std::weak_ptr<PropertyConfig> getPropertyConfig(const std::string& propertyName);
    void addPropertyConfig(const std::string& name, std::shared_ptr<PropertyConfig> config);

    // Property transfer methods
    void transferProperty(const std::weak_ptr<Player>& toPlayer, const std::weak_ptr<OwnableProperty>& property); // Player to Player
    void transferProperty(const std::weak_ptr<OwnableProperty>& property); // Player to school
    void transferProperty(const std::weak_ptr<OwnableProperty>& property, const std::weak_ptr<Player>& toPlayer); // School to player

    // Fund Transfer methods
    void transferFunds(const std::weak_ptr<Player>& fromPlayer, const std::weak_ptr<Player>& toPlayer, int amount);
    void transferFunds(const std::weak_ptr<Player>& fromPlayer, int amount); // Player to school
    void transferFunds(int amount, const std::weak_ptr<Player>& toPlayer); // school to Player

    // Player utility
    int countGymsOwnedBy(const Player& player) const;
    int countResOwnedBy(const Player& player) const;

    int getLiquidAssets(const std::weak_ptr<Player>& player) const;
    bool checkBankrupt(const std::weak_ptr<Player>& player, int amount) const;

    void buyImprovement(const std::weak_ptr<OwnableProperty>& property);
    void sellImprovement(const std::weak_ptr<OwnableProperty>& property);

    void mortgageProperty(const std::weak_ptr<OwnableProperty>& property);
    void unmortgageProperty(const std::weak_ptr<OwnableProperty>& property);
};  

#endif // SCHOOL_H
