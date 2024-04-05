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
    // refrence to game board
    Board &board;
    // name of board text file
    std::string fname;
    // second array for textDisplay
    std::vector<std::vector<char>> display; 

public:
    // Constructor to read the text file containing the display of the board
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
