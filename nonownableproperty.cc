#include "nonownableproperty.h"

#include "bank.h"
#include "player.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

const int OSAP = 200;
const int TUITION = 300;
const int TUITION_PER = 10;
const int COOP_FEE = 150;
const int JAIL_FEE = 50;

NonOwnableProperty::NonOwnableProperty(std::string name, int loc): Tile{name, loc} {}
CollectOsap::CollectOsap(std::string name, int loc): NonOwnableProperty{name, loc} {}
DCTims::DCTims(std::string name, int loc): NonOwnableProperty{name, loc} {}
GoToTims::GoToTims(std::string name, int loc): NonOwnableProperty{name, loc} {}
GooseNesting::GooseNesting(std::string name, int loc): NonOwnableProperty{name, loc} {}
Tuition::Tuition(std::string name, int loc): NonOwnableProperty{name, loc} {}
CoopFee::CoopFee(std::string name, int loc): NonOwnableProperty{name, loc} {}
SLC::SLC(std::string name, int loc): NonOwnableProperty{name, loc} {}
NH::NH(std::string name, int loc): NonOwnableProperty{name, loc} {}



void CollectOsap::performAction(Player &p, Bank &b) {
    std::cout << "You have passed Collect Osap, Collect $" << OSAP << std::endl;
    b.transferFunds("BANK", p.getName(), OSAP);
}

void DCTims::performAction(Player &p, Bank &b) {
    if (p.isVisitingTims()) {
        std::cout << "You are vising " << this->getName() << std::endl;
        return;
    } 
    std::cout << "You are in the DCTims line, roll doubles, pay $" << JAIL_FEE;
    std::cout << ", or use a Roll up the Rim cup to exit the DCTims line" << std::endl;
    std::cout << "If you are in the line for 3 turns you fill be forced to use a Roll up the Rim cup or pay the fee" << std::endl;
    std::cout << "This is your " << p.getTimsLine() << " turn" << std::endl;

        if (p.getTimsLine() == 3) {
            std::cout << "You have stayed in the DCTims line for too long!" << std::endl;
            std::cout << "Use a Roll up the Rim cup or pay the fee of $" << JAIL_FEE << std::endl;
            p.toggleHasToPay();
        }
    p.incTimsLine();
}

void GoToTims::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on GoToTims, go directly to DCTims, if you pass OSAP do not collect $" << OSAP << std::endl;
    p.setPosition(10);
    p.toggleVisiting();
}

void GooseNesting::performAction(Player &p, Bank &b) {
    std::cout << p.getName() << " is attacked by a flock of wild geese!" << std::endl;
    return;
}

void Tuition::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on Tuition, enter 't' to pay $" << TUITION;
    std::cout << " or enter 'p' to pay %" << TUITION_PER << " of your total worth" << std::endl;
    std::string opt;
    int fee;

    while (true) {
        std::cin >> opt;
        if (opt == "t") {
            fee = TUITION;
            break;
        } else if (opt == "p") {
            fee = static_cast<float>(TUITION_PER) / 100 * p.getWallet();
            break;
        } else {
            std::cout << "Please enter either t or p" << std::endl;
        }
    }

    std::cout << "You have choosen to pay a fee of $" << fee << std::endl;
    p.toggleHasToPay();
    p.setFeeOwner("BANK");
    p.setFee(fee);
}

void CoopFee::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on Coop Fee, pay $" << COOP_FEE << std::endl;
    p.toggleHasToPay();
    p.setFeeOwner("BANK");
    p.setFee(COOP_FEE);
}


// Shuffles the given vector and returns the first element
// Simulates generating a random number in the set of integers in the vector passed
// Helper method for SCL::performAction and NH::performAction
int genRandNum(std::vector<int>& vec) {
    unsigned int currentTime = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 seed(currentTime); // Seeds random num generator with 
    std::shuffle(vec.begin(), vec.end(), seed); // Shuffles elements in vec
    return vec[0]; // returns first element of vec
}

void SLC::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on SLC" << std::endl;
    int n;

    if (b.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        std::vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);

        if (n == 1) { // Wins a get out of DCTims line
            std::cout << "You won a DC Tims cup!" << std::endl;
            p.addTimsCups(1);
            b.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probs
    std::vector<int> slcProbs{1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 
                               5, 5, 5, 5, 6, 6, 6, 6, 7, 8};
    n = genRandNum(slcProbs);
    int pos = 0;
    switch (n) { // switch case that matches SLC prob. table given in Watopoly.pdf
        case 1: pos = -3; break;
        case 2: pos = -2; break;
        case 3: pos = -1; break;
        case 4: pos = 1; break;
        case 5: pos = 2; break;
        case 6: pos = 3; break;
        case 7: pos = 0; break;
        case 8: pos = 10; break;
    }

    if (pos == 10) {
        std::cout << "You go to the DC Tims line" << std::endl;
        p.toggleVisiting();
        p.setPosition(pos);
    } else if (pos == 0) {
        std::cout << "You move to Collect Osap" << std::endl;
        p.setPosition(pos);
    } else {
        if (pos < 0) std::cout << "You move back " << -(pos) << " tiles" << std::endl;
        else std::cout << "You move forward " << pos << " tiles" << std::endl;
        p.movePosition(pos);
    }

}




void NH::performAction(Player &p, Bank &b) {
    std::cout << "You have landed on NH" << std::endl;
    int n;

    if (b.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        std::vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);
        if (n == 1) { // Wins a get out of DCTims line
            std::cout << "You won a DC Tims cup!" << std::endl;
            p.addTimsCups(1);
            b.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probs.
    std::vector<int> nhProbs{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    n = genRandNum(nhProbs);
    int fee = 0;
    int reward = 0;
    // May have to sell/mortgage assests, or declare bankrupcy if p.wallet goes less than 0
    switch(n) { // switch case that matches NH prob. table given in Watopoly.pdf
        case 1: fee = 200; break;
        case 2: fee = 100; break;
        case 3: fee = 50; break;
        case 4: reward = 25; break;
        case 5: reward = 50; break;
        case 6: reward = 100; break;
        case 7: reward = 200; break;
    }

    if (fee != 0) {
        std::cout << "You got unlucky and are being charged with a fee of $" << fee << std::endl;
        p.toggleHasToPay();
        p.setFeeOwner("BANK");
        p.setFee(fee);
    } else {
        std::cout << "You got lucky and are being given $" << reward << std::endl;
        b.transferFunds("BANK", p.getName(), reward);
    }
}
