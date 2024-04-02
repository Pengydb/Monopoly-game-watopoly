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

using namespace std;

class Board : public Observer {
    vector<Tile*> buildings; // Stores pointers to buildings on the board
    vector<Player*> players; // Stores pointers to players on the board
    School school; // Instance of the school
    int playerTurn; // Stores the current player's turn

    public:
    void saveGame(); // Saves the current game
    int getTurn(); // Gets the current player's turn
    void startGame(); // Starts the game

    void setPlayer(); // Creates a player
    void movePlayer(Player &p, Tile &t); // Moves a player to the target tile
    void removePlayer(Player &p); // removes a player from the board
    void nextTurn(); // moves the game to the next turn
    void playGame(); // Continues playing the game
    void printBoard(); // Prints the current state of the board
};

#endif // BOARD_H
