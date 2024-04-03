#include "residence.h"
#include <iostream>
#include <string>
using namespace std;

Residence::Residence(string name, PropertyConfig& config, bool owned, bool mortgaged) :
            OwnableProperty{name, config, owned, mortgaged} {}

void Residence::performAction(Player &p, Bank &b) {
    cout << "You have landed on " << this->getName() << endl;

    if (this->isOwned()) { // Property is already owned
        int fee = this->getFee();
        cout << "You are charged a fee of $" << fee << endl;
        b.transferFunds("BANK", p.getName(), -fee);

    } else { // Property is unowned
        cout << "Do you want to buy " << this->getName() << " for $" << config.getCost() << "? (y/n)" << endl;
        string ans;
        while (true) {
            cin >> ans;
            if (ans == "y") { // Player Buys Property
                b.transferFunds("BANK", p.getName(), -config.getCost());
                b.transferProperty(p.getName(), this->getName());
            } else if (ans == "n") { // Property goes up for auction
                b.holdAuction(this->getName());
            }
        }
    }
}