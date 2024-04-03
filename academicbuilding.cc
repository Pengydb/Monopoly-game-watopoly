#include "academicbuilding.h"
#include <iostream>
#include <string>
using namespace std;

AcademicBuilding::AcademicBuilding(string name, PropertyConfig& config, bool owned, bool mortgaged, 
                                   int impCount, int impCost):
                    OwnableProperty{name, config, owned, mortgaged}, impCount{impCount}, impCost{impCost} {}

void AcademicBuilding::performAction(Player &p, Bank &b) {
    cout << "You have landed on " << this->getName() << endl;

    if (this->isOwned()) { // Property is already owned
        int fee = config.getFee(impCount);
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