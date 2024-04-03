#include "residence.h"
#include <iostream>
#include <string>

Residence::Residence(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged) :
            OwnableProperty{name, loc, config, owned, mortgaged} {}

void Residence::performAction(Player &p, School &s) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) { // Property is already owned
        int fee = this->getFee();
        std::cout << "You are charged a fee of $" << fee << std::endl;
        s.transferFunds("SCHOOL", p.getName(), -fee);

    } else { // Property is unowned
        std::cout << "Do you want to buy " << this->getName() << " for $" << config.getCost() << "? (y/n)" << std::endl;
        std::string ans;
        while (true) {
            std::cin >> ans;
            if (ans == "y") { // Player Buys Property
                s.transferFunds("SCHOOL", p.getName(), -config.getCost());
                s.transferProperty(p.getName(), this->getName());
            } else if (ans == "n") { // Property goes up for auction
                s.holdAuction(this->getName());
            }
        }
    }
}