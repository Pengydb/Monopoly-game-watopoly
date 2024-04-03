#include "gym.h"
#include "school.h"
#include <iostream>
#include <string>

Gym::Gym(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged) :
            OwnableProperty{name, loc, config, owned, mortgaged} {}

void Gym::performAction(Player &p, School &s) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) { // Property is already owned
        int fee = this->getFee();
        std::cout << "Roll the dice" << std::endl;
        
        while(true) {
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "roll") {
                int r = p.roll() + p.roll();
                std::cout << "You rolled a sum of " << r << std::endl;
                fee = fee*r;
                std::cout << "You are charged $" << fee << std::endl;
                s.transferFunds("SCHOOL", p.getName(), -fee);
            }
        }

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