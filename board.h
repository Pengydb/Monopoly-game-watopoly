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
    // Stores pointers to all tiles on the board
    std::vector<std::shared_ptr<Tile>> & buildings;
    // Stores pointers to players on the board
    std::vector<std::shared_ptr<Player>> & players;
    // Instance of the bank
    std::shared_ptr<Bank> bank;
    // Stores the current player's turn
    int playerTurn;
  public:
      // Saves the current game
      void saveGame();
      // Loads the game
      void loadGame(const std::string &filename);
      // Gets the current player's turn
      int getTurn();
      // Starts the game
      void setupGame(const std::string &filename);
      // Plays the game
      void playGame();

      // Creates a player
      std::shared_ptr<Player> setPlayer(std::map<std::string, char> &nameToPiece);
      // Moves a player to the target tile
      void movePlayer(Player &p, int roll);
      // removes a player from the board
      void removePlayer(Player &p);

      // Prints the current state of the board
      void printBoard(); 
      // Loads a saved game
      void loadGame(const std::string &filename);

      // Returns the name of the tile at position n (assumes 40 >= n >= 0)
      std::string getTileName(const int n) const;
      // Returns the cost of the property at position n (assumes n corresponds to the position of an ownable property)
      int getPropCost(const int n) const;

      // moves the game to the next turn
      void nextTurn();
      // Notifies the subjects of any changes
      void notify(Player &p);
      // Prints the current state of the board
      void printBoard(TextDisplay &t);
      // Checks if the player with name 'name' is in the game
      bool playerExists(std::string name);
};

#endif // BOARD_H
