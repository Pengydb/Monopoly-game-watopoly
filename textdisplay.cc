#include "textdisplay.h"
#include <iostream>
#include <string>
#include <fstream>
#include "board.h"


// Default Board: Tiles 8x7 characters in size
TextDisplay::TextDisplay(Board& board, std::vector<std::shared_ptr<Player>> players, std::string fname): 
                         board{board}, players{players}, fname{fname} {
    std::ifstream file{fname};
    if (!file.is_open())
    {
        throw std::invalid_argument("Error opening file " + fname);
    }

    std::string line;
    std::vector<char> row;
    while (std::getline(file, line)) {
        row.insert(row.end(), line.begin(), line.end());
        display.emplace_back(row);
        row.clear();
    }

    int r = 65;
    int c = 93;
    for (auto p : players) {
        display[r][c];
        c += 2;
        if (c >= 100) r++;
    }
}


void TextDisplay::notify(Player& p) {
    int pos = p.getPosition();
    int numP = board.playersAtPos(pos); // number of players at this tile
    int r, c, rinc, cinc; // Row : Column : Row increment and Column increment (for when numP > 1)
    
    
    if (numP > 4) {
        cinc = (numP-4)*2;
        rinc = 1;
    } else {
        cinc = numP*2;
        rinc = 0;
    }
    
    if (0 <= pos <= 10) { // Bottom Row
        r = 65 + rinc;
        c = 92 - pos*10 + cinc;
        
    } else if (11 <= pos <= 19) { // Left Side
        r = 65 - (pos-10)*6 + rinc;
        c = 2 + cinc;

    } else if (20 <= pos <= 30) { // Top Row
        r = 5 + rinc;
        c = 2 + (pos-19)*10 + cinc;

    } else { // Right Side
        r = 5 + (pos-30)*6 + rinc;
        c = 92 + cinc;
    }

    display[r][c] = p.getPiece();
}

void TextDisplay::notify(AcademicBuilding& a) {
    int loc = a.getLocation();
    int imps = a.getImpCount();
    int r, c; // Row : Column : Row increment (for when numP > 1)

    if (0 <= loc <= 10) { // Bottom Row
        r = 62;
        c = 92 - loc*10 + (imps - 1);
        
    } else if (11 <= loc <= 19) { // Left Side
        r = 62 - (loc-10)*6;
        c = 2 + (imps - 1);

    } else if (20 <= loc <= 30) { // Top Row
        r = 2;
        c = 2 + (loc-19)*10 + (imps - 1);

    } else { // Right Side
        r = 2 + (loc-30)*6;
        c = 92 + (imps - 1);

    }

    display[r][c] = 'I';
}

void TextDisplay::printBoard() const {
    for (auto r : display) {
        for(auto c : r) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}


