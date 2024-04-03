#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "observer.h"
#include "tile.h"
#include "academicbuilding.h"
#include "nonownableproperty.h"
#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "player.h"
#include "bank.h"
#include "textdisplay.h"

class Board : public Observer {
    std::vector<std::shared_ptr<Tile>> & buildings; // Stores pointers to buildings on the board
    std::vector<std::shared_ptr<Player>> & players;  // Stores pointers to players on the board
    std::shared_ptr<Bank> bank; // Instance of the bank
    int playerTurn; // Stores the current player's turn

  public:
    void saveGame(); // Saves the current game
    void loadGame(const std::string &filename); // Loads the game
    int getTurn(); // Gets the current player's turn
    void setupGame(const std::string &filename); // Starts the game
    void playGame(); // Plays the game

    std::shared_ptr<Player> setPlayer(std::map<std::string, char> &nameToPiece); // Creates a player
    void movePlayer(Player &p, int roll); // Moves a player to the target tile
    void removePlayer(Player &p); // removes a player from the board

    void printBoard(); // Prints the current state of the board
    // void notify(Subject &s);
    void loadGame(const std::string &filename);

    // Returns the name of the tile at position n (assumes 40 >= n >= 0)
    std::string getTileName(const int n) const; 
    // Returns the cost of the property at position n (assumes n corresponds to the position of an ownable property)
    int getPropCost(const int n) const;

    void nextTurn(); // moves the game to the next turn
    void notify(Player &p); // Notifies the subjects of any changes
    void printBoard(TextDisplay &t); // Prints the current state of the board
    bool playerExists(std::string name); // Checks if the player with name 'name' is in the game
};

#endif // BOARD_H
