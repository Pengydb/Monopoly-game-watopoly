#include "academicbuilding.h"
#include "player.h"
#include "propertyconfig.h"
#include "bank.h"
#include <iostream>
#include <string>

AcademicBuilding::AcademicBuilding(std::string name, int loc, std::shared_ptr<PropertyConfig> config, bool owned, bool mortgaged, 
                                   int impCount):
                    OwnableProperty{name, loc, config, owned, mortgaged}, impCount{impCount}{}

const int monopolyMultiplier = 2;

void AcademicBuilding::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on " << this->getName() << std::endl;

    if (this->isOwned()) {
        std::string owner = b.getPropertyOwner(this->getName());
        std::cout << "This property is owned by " << owner << std::endl;

        if (p.getName() == owner) {
            std::cout << p.getName() <<  ", you do not need to pay tuition as you are the owner." << std::endl;
            return;
        }

        if (this->isMortgaged()) {
            std::cout << "The property is currently mortgaged. No tuition fees will be charged." << std::endl;
            return;
        }  

        int fee = config->getFee(this->getImpCount());

        if (getMonopoly() && getImpCount() < 1) fee *= monopolyMultiplier;
        
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
    impCount += n;
    this->notifyObservers(); 
}
int AcademicBuilding::getImpCost() const { return config->getImpCost(); }
bool AcademicBuilding::getMonopoly() const { return monopoly; }
void AcademicBuilding::toggleMonopoly() { monopoly = !(monopoly); }
void AcademicBuilding::setMonopoly(bool status) { monopoly = status; }
int AcademicBuilding::getImpCount() const { return impCount; }

