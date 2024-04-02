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
#include "textdisplay.h"

class Board : public Observer {
    std::vector<std::shared_ptr<Tile>> & buildings; // Stores pointers to buildings on the board
    std::vector<std::shared_ptr<Player>> & players;  // Stores pointers to players on the board
    std::shared_ptr<School> school; // Instance of the school
    std::vector<std::shared_ptr<Observer>> observers; // Stores all of the observers
    int playerTurn; // Stores the current player's turn

    public:
    void saveGame(); // Saves the current game
    void loadGame(const std::string &filename); // Loads the game
    int getTurn(); // Gets the current player's turn
    void setupGame(const std::string &filename); // Starts the game
    void playGame(); // Plays the game

    std::shared_ptr<Player> setPlayer(); // Creates a player
    void movePlayer(Player &p, int roll); // Moves a player to the target tile
    void removePlayer(Player &p); // removes a player from the board
<<<<<<< HEAD
    void printBoard(); // Prints the current state of the board
    // void notify(Subject &s);
    void loadGame(const std::string &filename);

    // Returns the name of the tile at position n (assumes 40 >= n >= 0)
    std::string getTileName(const int n) const; 
=======
    void nextTurn(); // moves the game to the next turn
    void notify(Subject &s); // Notifies the subjects of any changes
    void printBoard(TextDisplay &t); // Prints the current state of the board
>>>>>>> 5a1eade (changes done to board)
};

#endif // BOARD_H
