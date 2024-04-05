#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "subject.h"
#include <string>

class Bank;

class Player: public Subject {
private:
    // Stores the player's piece
    char piece;
    // Stores the name of the player
    std::string name;
    // Stores the amount of money they have
    int wallet;
    // Stores the number of tiles of the board
    int boardSize;
    // Stores the player's current position
    int position;
    // true when visting false when in line
    bool visitingTims;
    // number of turns in line
    int timsLine; 
    // Stores the number of Roll up the Rim cups
    int timsCups;
    // Number of gyms the player owns
    int gyms;
    // Number of residences the player owns
    int res;
    // True if player has landed on an unowned property, registers that the player has the ability to buy this property
    bool buy;
    // True if the player has to pay a fee before ending their turn
    bool pay;
    // The fee the player must pay before ending thier turn
    int fee;
    // Who the player pays the fee to (BANK if not ownable property fee)
    std::string feeOwner; 
public:
    // Constructor to initialize all necessary fields
    Player(char piece, const std::string &name, int wallet, int boardSize = 40, int position = 0, bool visitingTims = true,
           int timsLine = 0, int timsCups = 0, int gyms = 0, int res = 0, bool buy = false, bool pay = false, int fee = 0, std::string feeOwner = "");

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
   void movePosition(const int n); 
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
