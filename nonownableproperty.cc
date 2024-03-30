#include "nonownableproperty.h"
#include <iostream>
using namespace std;

static int OSAP = 200;
static int TUITION = 300;
static int TUITION_PER = 10;
static int COOP_FEE = 150;

void CollectOsap::performAction(Player &p) {
    cout << "You have passed Collect Osap, Collect $" << OSAP << endl;
    p.incWallet(OSAP);
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

    if (n == 1) p.incWallet(-TUITION);
    else p.incWallet(-(TUITION_PER/100)*p.getWallet());
}

void CoopFee::performAction(Player &p) {
    cout << "You have landed on Coop Fee, pay $" << COOP_FEE << "top the School" << endl;
    p.incWallet(-COOP_FEE);
}

void SLC::performAction(Player &p) {
    cout << "You have landed on SCL" << endl;
}

void NH::performAction(Player &p) {
    cout << "You have landed on NH" << endl;
}