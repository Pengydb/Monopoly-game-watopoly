#include "academicbuilding.h"
#include <iostream>
#include <string>

AcademicBuilding::AcademicBuilding(std::string name, int loc, bool owned, bool mortgaged, 
                                   int impCount, int impCost):
                    OwnableProperty{name, loc, owned, mortgaged}, impCount{impCount}, impCost{impCost} {}



void AcademicBuilding::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) {
        std::string owner = b.getPropertyOwner(this->getName());
        std::cout << "This property is owned by " << owner << std::endl;
        int fee = config->getFee(impCount);
        std::cout << "You are being charged with a fee of $" << fee << std::endl;
        p.toggleHasToPay();
        p.setFee(fee);
        p.setFeeOwner(owner);
    } else {
        std::cout << "This property is unowned! You have the option to buy it for $" << config->getCost() << std::endl;
        p.toggleCanBuy();
    }
}


void AcademicBuilding::addImps(const int n) { 
    impCount + n;
    this->notifyObservers(); 
}
int AcademicBuilding::getImpCost() const { return config->getImpCost(); }
bool AcademicBuilding::getMonopoly() const { return monopoly; }
void AcademicBuilding::toggleMonopoly() { monopoly = !(monopoly); }
void AcademicBuilding::setMonopoly(bool status) { monopoly = status; }
int AcademicBuilding::getImpCount() const { return impCount; }

