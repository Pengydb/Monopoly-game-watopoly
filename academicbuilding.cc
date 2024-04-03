#include "academicbuilding.h"
#include <iostream>
#include <string>

AcademicBuilding::AcademicBuilding(std::string name, int loc, PropertyConfig& config, bool owned, bool mortgaged, 
                                   int impCount, int impCost):
                    OwnableProperty{name, loc, config, owned, mortgaged}, impCount{impCount}, impCost{impCost} {}



void AcademicBuilding::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) { // Property is already owned
        int fee = config.getFee(impCount);
        std::cout << "You are charged a fee of $" << fee << std::endl;
        b.transferFunds("BANK", p.getName(), -fee);

    } else { // Property is unowned
        std::cout << "Do you want to buy " << this->getName() << " for $" << config.getCost() << "? (y/n)" << std::endl;
        std::string ans;
        while (true) {
            std::cin >> ans;
            if (ans == "y") { // Player Buys Property
                b.transferFunds("BANK", p.getName(), -config.getCost());
                b.transferProperty(p.getName(), this->getName());
            } else if (ans == "n") { // Property goes up for auction
                b.holdAuction(this->getName());
            }
        }
    }
}


void AcademicBuilding::addImps(const int n) { impCount + n; }
int AcademicBuilding::getImpCost() const { return impCost; }
bool AcademicBuilding::getMonopoly() const { return monopoly; }
void AcademicBuilding::toggleMonopoly() { monopoly = !(monopoly); }
void AcademicBuilding::setMonopoly(bool status) { monopoly = status; }
int AcademicBuilding::getImpCount() const { return impCount; }
void AcademicBuilding::sellImps(Bank &b, Player &p, int n) {
    impCount -= n;
    b.transferFunds("SCHOOL", p.getName(), n*impCost*(0.5));
}
