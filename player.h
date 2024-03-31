#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include "school.h"
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
    void addWallet(const int amount); // adds amount to wallet field
    char getPiece();
    void setPosition(const int pos);
    int getPosition() const; // Returns position field
    int movePosition(const int n); // moves player forward or backwards (if n < 0) by n tiles
    int getTimsLine();
    void setTimsLine(const int pos);
    int incTimsLine() const; // increments timsLine by 1
    bool isVisitingTims() const; // returns visitingTims field;
    void toggleVisiting(); // Toggles visitingTims to opposite of what it was
    void getTimsCups() const; // returns timsCups field
    void addTimsCups(const int n); // Adds n to timsCups field

    std::string getName();
};

#endif // PLAYER_H
