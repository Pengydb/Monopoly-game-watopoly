#ifndef _NONOWNABLEPROPERTY_H_
#define _NONOWNABLEPROPERTY_H_

#include "tile.h"

class Bank;


class NonOwnableProperty : public Tile {
  public:
    // Constructor to initialize the name of the tile and its location
    NonOwnableProperty(std::string name, int loc);
    // This is a pure virtual method that must be implemented by derived classes.
    virtual void performAction(Player &p, Bank &b) = 0;
};


class CollectOsap : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    CollectOsap(std::string name, int loc);
    // Performs the process of crediting money when passing the CollectOSAP tile
    void performAction(Player &p, Bank &b) override; 
};

class DCTims : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    DCTims(std::string name, int loc);
    // Informs the player about the the tile and prompts to pay if the player stays for more than 3 turns
    void performAction(Player &p, Bank &b) override;
};

class GoToTims : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    GoToTims(std::string name, int loc);
    // Sets the position of the player to the DC Tims line
    void performAction(Player &p, Bank &b) override;
};

class GooseNesting : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    GooseNesting(std::string name, int loc);
    // Prints a message that the player has been attacked by wild geese
    void performAction(Player &p, Bank &b) override;
};

class Tuition : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    Tuition(std::string name, int loc);
    // Prompts the player to pay for Tuition
    void performAction(Player &p, Bank &b) override;
};

class CoopFee : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    CoopFee(std::string name, int loc);
    // Prompts the player to pay for the Coop Fee
    void performAction(Player &p, Bank &b) override;
};

class SLC : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    SLC(std::string name, int loc);
    // Performs the probabilities of SLC and outputs the action that has been taken
    void performAction(Player &p, Bank &b) override;
};

class NH : public NonOwnableProperty {
  public:
    // Constructor to initialize the name of the tile and its location
    NH(std::string name, int loc);
    // Performs the probabilities of Needles Hall and outputs the action that has been taken
    void performAction(Player &p, Bank &b) override;
};

#endif // NONOWNABLEPROPERTY_H
