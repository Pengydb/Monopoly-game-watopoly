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
    Board& board; // refrence to game board
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::vector<char>> display; // 2d array for textDisplay

public:
    TextDisplay(Board& board);
    void UpdateDisplay(std::shared_ptr<Tile> tile);
    void notify(Subject& subject) override;
    void printBoard() const;
};

#endif // TEXTDISPLAY_H
