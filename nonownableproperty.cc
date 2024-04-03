#include "nonownableproperty.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

const int OSAP = 200;
const int TUITION = 300;
const int TUITION_PER = 10;
const int COOP_FEE = 150;
const int JAIL_FEE = 50;

NonOwnableProperty::NonOwnableProperty(string name): Tile{name} {}
CollectOsap::CollectOsap(string name): NonOwnableProperty{name} {}
DCTims::DCTims(string name): NonOwnableProperty{name} {}
GoToTims::GoToTims(string name): NonOwnableProperty{name} {}
GooseNesting::GooseNesting(string name): NonOwnableProperty{name} {}
Tuition::Tuition(string name): NonOwnableProperty{name} {}
CoopFee::CoopFee(string name): NonOwnableProperty{name} {}
SLC::SLC(string name): NonOwnableProperty{name} {}
NH::NH(string name): NonOwnableProperty{name} {}



void CollectOsap::performAction(Player &p, Bank &b) {
    cout << "You have passed Collect Osap, Collect $" << OSAP << endl;
    b.transferFunds("BANK", p.getName(), OSAP);
}

void DCTims::performAction(Player &p, Bank &b) {
    if (p.isVisitingTims()) {
        cout << "You are vising DCTims" << endl;
        return;
    } 

    p.incTimsLine();

    cout << "You are in the DCTims line, roll doubles, pay $" << JAIL_FEE;
    cout << ", wait 5 turns, or use a Tims Cup to be free!" << endl;
    cout << "This is your " << p.getTimsLine() << " turn" << endl;


    if (p.getTimsCups() > 0) {
        cout << "You have a Tims Cup! Do you want to use it? (y/n)" << endl;
        while (true) {
            string ans;
            cin >> ans;
            if (ans == "y") {
                cout << "You are free from the line!" << endl;
                p.toggleVisiting();
                p.setTimsLine(0);
                b.addDCTimsCups(-1);
                return;
            } else if (ans == "n") {
                cout << "You remain in the line" << endl;
                break;
            }
        }
    }

    if (p.getWallet() > 50) {
        cout << "You have enough money to escape the line! Do you wish to pay $" << JAIL_FEE << "? (y/n)" << endl;
        while (true) {
            string ans;
            cin >> ans;
            if (ans == "y") {
                cout << "You are free from the line!" << endl;
                b.transferFunds("BANK", p.getName(), JAIL_FEE);
                p.toggleVisiting();
                p.setTimsLine(0);
                return;
            } else if (ans == "n") {
                cout << "You remain in the line" << endl;
                break;
            }
        }
    }

    if (p.getTimsLine() == 3) {
        cout << "You have stayed in the Tims line for too long either pay $" << JAIL_FEE;
        cout << ", or use a DCTims Cup" << endl;
        
        if (p.getTimsCups() == 0) {
            cout << "You don't have any TimsCups so you will pay the fee" << endl;
            b.transferFunds("BANK", p.getName(), JAIL_FEE);
        } else {
            p.addTimsCups(-1);
        }

        p.toggleVisiting();
        p.setTimsLine(0);
        return;
    } 
}

void GoToTims::performAction(Player &p, Bank &b) {
    cout << "You have landed on GoToTims, go directly to DCTims, if you pass OSAP do not collect $" << OSAP << endl;
    p.setPosition(10);
    p.toggleVisiting();
}

void GooseNesting::performAction(Player &p, Bank &b) {
    return;
}

void Tuition::performAction(Player &p, Bank &b) {
    cout << "You have landed on Tuition, enter 1 to pay $" << TUITION;
    cout << " or enter 2 to pay %" << TUITION_PER << " of your total worth" << endl;
    int n;
    cin >> n;

    if (n == 1) b.transferFunds("BANK", p.getName(), -TUITION);
    else b.transferFunds("BANK", p.getName(), -(TUITION_PER/100)*p.getWallet());
}

void CoopFee::performAction(Player &p, Bank &b) {
    cout << "You have landed on Coop Fee, pay $" << COOP_FEE << "top the Bank" << endl;
    b.transferFunds("BANK", p.getName(), (-COOP_FEE));
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

void SLC::performAction(Player &p, Bank &b) {
    cout << "You have landed on SCL" << endl;
    int n;

    if (b.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);

        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            b.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probs
    vector<int> slcProbs{1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 
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




void NH::performAction(Player &p, Bank &b) {
    cout << "You have landed on NH" << endl;
    int n;

    if (b.getDCTimsCups() < 4) { // Checks if amount of tim cups that all players have is < 4
        vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = genRandNum(timCupProb);
        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            b.addDCTimsCups(1);
            return;
        }
    } 

    // Regular Probb.
    vector<int> nhProbs{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    n = genRandNum(nhProbs);
    
    // May have to sell/mortgage assests, or declare bankrupcy if p.wallet goes less than 0
    switch(n) { // switch case that matches NH prob. table given in Watopoly.pdf
        case 1: b.transferFunds("BANK", p.getName(), -200);
        case 2: b.transferFunds("BANK", p.getName(), -100);
        case 3: b.transferFunds("BANK", p.getName(), -50);
        case 4: b.transferFunds("BANK", p.getName(), 25);
        case 5: b.transferFunds("BANK", p.getName(),50);
        case 6: b.transferFunds("BANK", p.getName(), 100);
        case 7: b.transferFunds("BANK", p.getName(), 200);
    }
}