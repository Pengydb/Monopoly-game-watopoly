#include "residence.h"
#include <iostream>
#include <string>
using namespace std;


void Residence::performAction(Player &p, School &s) {
    cout << "You have landed on " << this->getName() << endl;

    if (this->isOwned()) { // Property is already owned
        int fee = this->getFee();
        cout << "You are charged a fee of $" << fee << endl;
        s.transferFunds("SCHOOL", p.getName(), -fee);

    } else { // Property is unowned
        cout << "Do you want to buy " << this->getName() << " for $" << config.getCost() << "? (y/n)" << endl;
        string ans;
        while (true) {
            cin >> ans;
            if (ans == "y") { // Player Buys Property
                s.transferFunds("SCHOOL", p.getName(), -config.getCost());
                s.transferProperty(p.getName(), this->getName());
            } else if (ans == "n") { // Property goes up for auction
                s.holdAuction(this->getName());
            }
        }
    }
}