#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include <ownableproperty.h>
#include <string>

class Player: public Subject {
private:
    char piece;
    std::string name;
    int wallet;
    int position;
    bool bankrupt;
    bool visitingTims;  // true when visting false when in line
    int timsLine; // number of turns in line
    int timsCups;
    School& school;

public:
    Player(char piece, const std::string& name, int wallet, int position = 0, bool bankrupt = false, bool visitingTims = true, int timsLine = 0, 
           int timsCups = 0);
    int countGym();
    int countRest();
    void printAssets();
    void isBankrupt();
    int getWallet();
    void setWallet(const int amount);
    void incWallet(const int amount); // Increments the players wallet by amount
    char getPiece();
    void setPosition(const int pos);
    int getTimsLine();
    void setTimsLine(const int pos);
    std::string getName();
};

#endif // PLAYER_H
