#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include "bank.h"
#include <ownableproperty.h>
#include <string>

class Player: public Subject {
private:
    char piece;
    std::string name;
    int wallet;
    int boardSize;
    int position;
    bool visitingTims;  // true when visting false when in line
    int timsLine; // number of turns in line
    int timsCups;
    int gyms; // Number of gyms the player owns
    int res; // Number of residences the player owns
    Bank& bank;

public:
    Player(char piece, const std::string& name, int wallet, Bank& bank, int boardSize, int position = 0, bool visitingTims = true, 
           int timsLine = 0, int timsCups = 0, int gyms, int res);
    int getGyms() const; // Returns gyms field
    int getRes() const; // Returns res field
    void addGyms(const int n); // Adds n to the gyms field
    void addRes(const int n); // Adds n to the res field
    void printAssets() const;
    int getWallet() const;
    void setWallet(const int amount);
    void addWallet(const int amount); // adds amount to wallet field
    char getPiece() const;
    void setPosition(const int pos);
    int getPosition() const; // Returns position field
    int movePosition(const int n); // moves player forward or backwards (if n < 0) by n tiles
    int getTimsLine() const;
    void setTimsLine(const int pos);
    void incTimsLine(); // increments timsLine by 1
    bool isVisitingTims() const; // returns visitingTims field;
    void toggleVisiting(); // Toggles visitingTims to opposite of what it was
    int getTimsCups() const; // returns timsCups field
    void addTimsCups(const int n); // Adds n to timsCups field
    std::string getName() const;
    int roll() const; // Returns a random num between 1 and 6

    // Will continue to prompt player to sell improvements or mortgage their properties
    // Until their wallet is > 0 (assumes p.getWallet() < 0)
    void notEnoughCash(Bank &s); 
};

#endif // PLAYER_H
