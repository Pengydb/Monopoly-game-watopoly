#include "gym.h"
#include "bank.h"
#include "propertyconfig.h"
#include "ownableproperty.h"
#include "player.h"
#include <iostream>
#include <string>

Gym::Gym(std::string name, int loc, std::shared_ptr<PropertyConfig> config, bool owned, bool mortgaged) :
            OwnableProperty{name, loc, config, owned, mortgaged} {}

void Gym::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) {
        std::string ownerName = b.getPropertyOwner(this->getName());
        std::cout << "This property is owned by " << ownerName << std::endl;
        
        if (p.getName() == ownerName) {
            std::cout << p.getName() <<  ", you do not need to pay tuition as you are the owner." << std::endl;
            return;
        }     
           
        std::string cmd;
        int sum;
        while (true) {
            std::cout <<  "roll to calculate your fee" << std::endl;
            std::cin >> cmd;
            if (cmd == "roll") {
                sum = p.roll() + p.roll();
                break;
            }
        }

        
        std::shared_ptr<Player> owner = b.getPlayer(ownerName);
        int base = config->getFee(std::max(owner->getGyms() - 1, 0));
        std::cout << ownerName << " has " << owner->getGyms() << " gyms." << std::endl;
        std::cout << "Base fee $ " << base << std::endl;
        std::cout << "Multiplier from roll " << sum << std::endl;
    
        int fee = base * sum;
        std::cout << "You are being charged with a fee of $" << fee << std::endl;
        p.toggleHasToPay();
        p.setFee(fee);
        p.setFeeOwner(ownerName);
    } else {
        std::cout << "This property is unowned! You have the option to buy it for $" << config->getCost() << std::endl;
        p.toggleCanBuy();
    }
}