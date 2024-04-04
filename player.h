#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include "bank.h"
#include "ownableproperty.h"
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
    
    // returns buy field
    bool canBuy() const; 
    // returns pay field
    bool hasToPay() const; 
    // toggles buy field
    void toggleCanBuy(); 
    // toggles pay field
    void toggleHasToPay(); 
    // returns fee
    int getFee() const; 
    // sets fee to n
    void setFee(const int n); 
    // sets feeOwner
    void setFeeOwner(std::string owner); 
    // returns feeOwner
    std::string getFeeOwner() const; 
    // Returns number of gyms the player owns
    int getGyms() const; 
    // Returns the number of residences the player owns
    int getRes() const; 
    // Adds n to the number of gyms the player owns
    void addGyms(const int n); 
    // Adds n to the number of residences the player owns
    void addRes(const int n); 
    // Returns amount of money the player has
    int getWallet() const;
    // Sets players wallet to 'amount'
    void setWallet(const int amount);
    // Adds 'amount' to players wallet
    void addWallet(const int amount); 
    // Returns the players piece
    char getPiece() const;
    // Sets the players position
    void setPosition(const int pos);
    // Returns the players position
    int getPosition() const; 
    // moves player forward or backwards (if n < 0) by n tiles
    int movePosition(const int n); 
    // Returns the number of turns a player has been in the DCTims line
    int getTimsLine() const;
    // Sets the timsLine counter to n
    void setTimsLine(const int n);
    // Increments timsLine by 1
    void incTimsLine(); 
    // Returns whether player is visiting DCTims (true) or they are in the tims line (false)
    bool isVisitingTims() const; 
    // Toggles visitingTims to opposite of what it was
    void toggleVisiting(); 
    // Returns the number of Roll up the Rim cups the player has
    int getTimsCups() const; 
    // Adds n to the number of Roll up the Rim cups the player has
    void addTimsCups(const int n); 
    // Returns the players mame
    std::string getName() const;
    // Simulates rolling 1 die by return a random number between 1 and 6
    int roll() const; 

};

#endif // PLAYER_H
