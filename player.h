#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include <ownableproperty.h>
#include <string>

class Player: public Subject {
private:
    char piece;
    string name;
    int wallet;
    int position;
    bool bankrupt;
    bool visitingTims;  // true when visting false when in line
    int timsLine; // number of turns in line
    int timsCups;

public:
    int countGym();
    int countRest();
    void printAssets();
    void isBankrupt();
    int getWallet();
    void setWallet(const int amount);
    char getPiece();
    void setPosition(const int pos);
    int getTimsLine();
    void setTimsLine(const int pos);
    string getName();

    void buyProperty();
    void sellProperty();
    void buyImprovement();
    void sellImprovement();
    void mortgageProperty();
    void unmortgageProperty();

    void trade(Player target, OwnableProperty& b1, OwnableProperty& b2); // Property for Property
    void trade(Player target, OwnableProperty& b, const int cash); // Property for cash
    void trade(Player target, const int cash, OwnableProperty& b); // Cash for Property

};
#endif
