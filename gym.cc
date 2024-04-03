#include "gym.h"
#include "bank.h"
#include <iostream>
#include <string>

Gym::Gym(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged) :
            OwnableProperty{name, loc, config, owned, mortgaged} {}

void Gym::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) {
        std::string owner = b.getPropertyOwner(this->getName());
        std::cout << "This property is owned by " << owner << std::endl;
        
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

        int fee = config.getFee(p.getGyms()) * sum;
        std::cout << "You are being charged with a fee of $" << fee << std::endl;
        p.toggleHasToPay();
        p.setFee(fee);
        p.setFeeOwner(owner);
    } else {
        std::cout << "This property is unowned! You have the option to buy it for $" << config.getCost() << std::endl;
        p.toggleCanBuy();
    }
}