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
    Board &board;      // refrence to game board
    std::string fname; // board text file name
    std::vector<std::vector<char>> display; // 2d array for textDisplay

public:
    TextDisplay(Board& board, std::string fname = "default_board.txt");
    // Notify for when a player moves or when an improvement is added to an ownable property
    void notify(std::shared_ptr<Subject> s) override;
    // Updates the display, setting the position (corresponds to tile position)
    // to whitespace
    void cleanPos(const int pos, const char piece);
    // Prints the board
    void printBoard() const;
};

#endif // TEXTDISPLAY_H
