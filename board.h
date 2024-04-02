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
#include "school.h"

class Board : public Observer {
    std::vector<std::shared_ptr<Tile>> & buildings; // Stores pointers to buildings on the board
    std::vector<std::shared_ptr<Player>> & players;  // Stores pointers to players on the board
    std::shared_ptr<School> school; // Instance of the school
    int playerTurn; // Stores the current player's turn

    public:
    void saveGame(); // Saves the current game
    int getTurn(); // Gets the current player's turn
    void startGame(const std::string &filename); // Starts the game

    std::shared_ptr<Player> setPlayer(); // Creates a player
    void movePlayer(Player &p, int roll); // Moves a player to the target tile
    void nextTurn(); // moves the game to the next turn
    void removePlayer(Player &p); // removes a player from the board
    void printBoard(); // Prints the current state of the board
    // void notify(Subject &s);
    void loadGame(const std::string &filename);
};

#endif // BOARD_H
