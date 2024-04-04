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
    bool buy; // True if player has landed on an unowned property, registers that the player has the ability to buy this property
    bool pay; // True if the player has to pay a fee before ending their turn
    int fee; // The fee the player must pay before ending thier turn
    std::string feeOwner; // Who the player pays the fee to (BANK if not ownable property fee)
public:
    Player(char piece, const std::string& name, int wallet, Bank& bank, int boardSize, int position = 0, bool visitingTims = true, 
           int timsLine = 0, int timsCups = 0, int gyms, int res, bool buy, bool pay, int fee, std::string feeOwner);
    
    bool canBuy() const; // returns buy field
    bool hasToPay() const; // returns pay field
    void toggleCanBuy(); // toggles buy field
    void toggleHasToPay(); // toggles pay field
    int getFee() const; // returns fee
    void setFee(const int n); // sets fee to n
    void setFeeOwner(std::string owner); // sets feeOwner
    std::string getFeeOwner() const; // returns feeOwner
    
    int getGyms() const; // Returns gyms field
    int getRes() const; // Returns res field
    void addGyms(const int n); // Adds n to the gyms field
    void addRes(const int n); // Adds n to the res field
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

};

#endif // PLAYER_H
