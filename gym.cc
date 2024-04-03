#include "gym.h"
#include "bank.h"
#include <iostream>
#include <string>
using namespace std;

Gym::Gym(string name, PropertyConfig& config, bool owned, bool mortgaged) :
            OwnableProperty{name, config, owned, mortgaged} {}

void Gym::performAction(Player &p, Bank &b) {
    cout << "You have landed on " << this->getName() << endl;

    if (this->isOwned()) { // Property is already owned
        int fee = this->getFee();
        cout << "Roll the dice" << endl;
        
        while(true) {
            string cmd;
            cin >> cmd;
            if (cmd == "roll") {
                int r = p.roll() + p.roll();
                cout << "You rolled a sum of " << r << endl;
                fee = fee*r;
                cout << "You are charged $" << fee << endl;
                b.transferFunds("SCHOOL", p.getName(), -fee);
            }
        }

    } else { // Property is unowned
        cout << "Do you want to buy " << this->getName() << " for $" << config.getCost() << "? (y/n)" << endl;
        string ans;
        while (true) {
            cin >> ans;
            if (ans == "y") { // Player Buys Property
                b.transferFunds("SCHOOL", p.getName(), -config.getCost());
                b.transferProperty(p.getName(), this->getName());
            } else if (ans == "n") { // Property goes up for auction
                b.holdAuction(this->getName());
            }
        }
    }
}