#include "nonownableproperty.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

const int OSAP = 200;
const int TUITION = 300;
const int TUITION_PER = 10;
const int COOP_FEE = 150;

void CollectOsap::performAction(Player &p) {
    cout << "You have passed Collect Osap, Collect $" << OSAP << endl;
    p.addWallet(OSAP);
}

void DCTims::performAction(Player &p) {
    if (p.isVisitingTims()) {
        cout << "You are vising DCTims" << endl;
        return;
    } 

    cout << "You are in the DCTims line, roll doubles or wait 5 turns to be free!" << endl;
    cout << "This is your " << p.getTimsLine() << " turn";
    if (p.getTimsLine() == 5 /*|| p.roll() == "doubles"*/) { 
        cout << "You are free from the line!" << endl;
        p.toggleVisiting();
        p.setTimsLine(0);
    } else {
        p.incTimsLine();
    }
}

void GoToTims::performAction(Player &p) {
    cout << "You have landed on GoToTims, go directly to DCTims, if you pass OSAP do not collect $" << OSAP << endl;
    p.setPosition(10);
    p.toggleVisiting();
}

void GooseNesting::performAction(Player &p) {
    return;
}

void Tuition::performAction(Player &p) {
    cout << "You have landed on Tuition, enter 1 to pay $" << TUITION;
    cout << " or enter 2 to pay %" << TUITION_PER << " of your total worth" << endl;
    int n;
    cin >> n;

    if (n == 1) p.addWallet(-TUITION);
    else p.addWallet(-(TUITION_PER/100)*p.getWallet());
}

void CoopFee::performAction(Player &p) {
    cout << "You have landed on Coop Fee, pay $" << COOP_FEE << "top the School" << endl;
    p.addWallet(-COOP_FEE);
}


// Shuffles the given vector and returns the first element
int calculateProbs(std::vector<int>& vec) {
    std::random_device rd;
    std::mt19937 seed(rd()); // Seeds random num generator with random device
    std::shuffle(vec.begin(), vec.end(), seed); // Shuffles elements in vec
    return vec[0]; // returns first element of vec
}

void SLC::performAction(Player &p) {
    cout << "You have landed on SCL" << endl;
    int n;

    if (true) { // Checks if amount of tim cups that all players have is < 4
        vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = calculateProbs(timCupProb);

        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            return;
        }
    } 

    // Regular Probs
    vector<int> slcProbs{1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 
                               5, 5, 5, 5, 6, 6, 6, 6, 7, 8};
    n = calculateProbs(slcProbs);
    switch (n) { // switch case that matches prob. table given in Watopoly.pdf
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


void NH::performAction(Player &p) {
    cout << "You have landed on NH" << endl;
    int n;

    if (true) { // Checks if amount of tim cups that all players have is < 4
        vector<int> timCupProb(100, 0);
        timCupProb[0] = 1;
        n = calculateProbs(timCupProb);
        if (n == 1) { // Wins a get out of DCTims line
            p.addTimsCups(1);
            return;
        }
    } 

    // Regular Probs.
    vector<int> nhProbs{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    n = calculateProbs(nhProbs);
    

    // May have to sell/mortgage assests, or declare bankrupcy if p.wallet goes less than 0
    switch(n) {
        case 1: p.addWallet(-200);
        case 2: p.addWallet(-100);
        case 3: p.addWallet(-50);
        case 4: p.addWallet(25);
        case 5: p.addWallet(50);
        case 6: p.addWallet(100);
        case 7: p.addWallet(200);
    }
}