#include "nonownableproperty.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>

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



void CollectOsap::performAction(Player &p, School &s) {
    std::cout << "You have passed Collect Osap, Collect $" << OSAP << std::endl;
    s.transferFunds("SCHOOL", p.getName(), OSAP);
}

void DCTims::performAction(Player &p, School &s) {
    if (p.isVisitingTims()) {
        std::cout << "You are vising DCTims" << std::endl;
        return;
    } 

    p.incTimsLine();

    std::cout << "You are in the DCTims line, roll doubles, pay $" << JAIL_FEE;
    std::cout << ", wait 5 turns, or use a Tims Cup to be free!" << std::endl;
    std::cout << "This is your " << p.getTimsLine() << " turn" << std::endl;


    if (p.getTimsCups() > 0) {
        std::cout << "You have a Tims Cup! Do you want to use it? (y/n)" << std::endl;
        while (true) {
            std::string ans;
            std::cin >> ans;
            if (ans == "y") {
                std::cout << "You are free from the line!" << std::endl;
                p.toggleVisiting();
                p.setTimsLine(0);
                s.addDCTimsCups(-1);
                return;
            } else if (ans == "n") {
                std::cout << "You remain in the line" << std::endl;
                break;
            }
        }
    }

    if (p.getWallet() > 50) {
        std::cout << "You have enough money to escape the line! Do you wish to pay $" << JAIL_FEE << "? (y/n)" << std::endl;
        while (true) {
            std::string ans;
            std::cin >> ans;
            if (ans == "y") {
                std::cout << "You are free from the line!" << std::endl;
                s.transferFunds("SCHOOL", p.getName(), JAIL_FEE);
                p.toggleVisiting();
                p.setTimsLine(0);
                return;
            } else if (ans == "n") {
                std::cout << "You remain in the line" << std::endl;
                break;
            }
        }
    }

    if (p.getTimsLine() == 3) {
        std::cout << "You have stayed in the Tims line for too long either pay $" << JAIL_FEE;
        std::cout << ", or use a DCTims Cup" << std::endl;
        
        if (p.getTimsCups() == 0) {
            std::cout << "You don't have any TimsCups so you will pay the fee" << std::endl;
            s.transferFunds("SCHOOL", p.getName(), JAIL_FEE);
        } else {
            p.addTimsCups(-1);
        }

        p.toggleVisiting();
        p.setTimsLine(0);
        return;
    } 
}

void GoToTims::performAction(Player &p, School &s) {
    std::cout << "You have landed on GoToTims, go directly to DCTims, if you pass OSAP do not collect $" << OSAP << std::endl;
    p.setPosition(10);
    p.toggleVisiting();
}

void GooseNesting::performAction(Player &p, School &s) {
    return;
}

void Tuition::performAction(Player &p, School &s) {
    std::cout << "You have landed on Tuition, enter 1 to pay $" << TUITION;
    std::cout << " or enter 2 to pay %" << TUITION_PER << " of your total worth" << std::endl;
    int n;
    std::cin >> n;

    if (n == 1) s.transferFunds("SCHOOL", p.getName(), -TUITION);
    else s.transferFunds("SCHOOL", p.getName(), -(TUITION_PER/100)*p.getWallet());
}

void CoopFee::performAction(Player &p, School &s) {
    std::cout << "You have landed on Coop Fee, pay $" << COOP_FEE << "top the School" << std::endl;
    s.transferFunds("SCHOOL", p.getName(), (-COOP_FEE));
}


// Shuffles the given vector and returns the first element
// Simulates generating a random number in the set of integers in the vector passed
// Helper method for SCL::performAction and NH::performAction
int genRandNum(std::vector<int>& vec) {
    std::random_device rd;
    std::mt19937 seed(rd()); // Seeds random num generator with random device
    std::shuffle(vec.begin(), vec.end(), seed); // Shuffles elements in vec
    return vec[0]; // returns first element of vec
}

void SLC::performAction(Player &p, School &s) {
    std::cout << "You have landed on SCL" << std::endl;
    int n;

    if (s.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        std::vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);

        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            s.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probs
    std::vector<int> slcProbs{1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 
                               5, 5, 5, 5, 6, 6, 6, 6, 7, 8};
    n = genRandNum(slcProbs);
    switch (n) { // switch case that matches SCL prob. table given in Watopoly.pdf
        case 1: p.movePosition(-3); 
        case 2: p.movePosition(-2);
        case 3: p.movePosition(-1);
        case 4: p.movePosition(1);
        case 5: p.movePosition(2);
        case 6: p.movePosition(3);
        case 7: p.setPosition(0);
        case 8: p.setPosition(10); p.toggleVisiting();
    }

}




void NH::performAction(Player &p, School &s) {
    std::cout << "You have landed on NH" << std::endl;
    int n;

    if (s.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        std::vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);
        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            s.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probs.
    std::vector<int> nhProbs{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    n = genRandNum(nhProbs);
    
    // May have to sell/mortgage assests, or declare bankrupcy if p.wallet goes less than 0
    switch(n) { // switch case that matches NH prob. table given in Watopoly.pdf
        case 1: s.transferFunds("SCHOOL", p.getName(), -200);
        case 2: s.transferFunds("SCHOOL", p.getName(), -100);
        case 3: s.transferFunds("SCHOOL", p.getName(), -50);
        case 4: s.transferFunds("SCHOOL", p.getName(), 25);
        case 5: s.transferFunds("SCHOOL", p.getName(),50);
        case 6: s.transferFunds("SCHOOL", p.getName(), 100);
        case 7: s.transferFunds("SCHOOL", p.getName(), 200);
    }
}