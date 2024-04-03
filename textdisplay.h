#ifndef __TEXTDISPLAY_H_
#define __TEXTDISPLAY_H_

#include "observer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "board.h"
#include <memory>

class TextDisplay: public Observer {
private:
    std::string fname; // board text file name
    Board& board; // refrence to game board
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::vector<char>> display; // 2d array for textDisplay

public:
    TextDisplay(Board& board, std::vector<std::shared_ptr<Player>> players, std::string fname);
    void notify(Player& p);
    void notify(AcademicBuilding& a);
    void printBoard() const;
};

#endif // TEXTDISPLAY_H
