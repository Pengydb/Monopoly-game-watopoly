#ifndef __TEXTDISPLAY_H_
#define __TEXTDISPLAY_H_

#include "observer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>

class Board;
class Player;
class TextDisplay: public Observer {
private:
    std::string fname; // board text file name
    std::vector<std::shared_ptr<Player>> players;
    Board& board; // refrence to game board
    std::vector<std::vector<char>> display; // 2d array for textDisplay

public:
    TextDisplay(std::string fname, std::vector<std::shared_ptr<Player>> players, Board& board);
    // Notify for when a player moves
    void notify(std::shared_ptr<Subject> s) override;
    // Prints the board
    void printBoard() const;
};

#endif // TEXTDISPLAY_H
