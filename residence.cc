#include "residence.h"
#include "bank.h"
#include "player.h"
#include <iostream>
#include <string>

Residence::Residence(std::string name, int loc, std::shared_ptr<PropertyConfig> config, bool owned, bool mortgaged) : 
                    OwnableProperty{name, loc, config, owned, mortgaged} {}

void Residence::performAction(Player &p, Bank &b)
{
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned())
    {
        std::string owner = b.getPropertyOwner(this->getName());
        std::cout << "This property is owned by " << owner << std::endl;
        int fee = config->getFee(p.getRes());

        std::cout << "You are being charged with a fee of $" << fee << std::endl;
        p.toggleHasToPay();
        p.setFee(fee);
        p.setFeeOwner(owner);
    }
    else
    {
        std::cout << "This property is unowned! You have the option to buy it for $" << config->getCost() << std::endl;
        p.toggleCanBuy();
    }
}
