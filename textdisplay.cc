#include "textdisplay.h"
#include <iostream>
#include <string>
#include <fstream>
#include "board.h"


// Default Board: Tiles 8x7 characters in size
TextDisplay::TextDisplay(Board& board, std::string fname): 
                         board{board}, fname{fname} {
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
}


void TextDisplay::notify(std::shared_ptr<Subject> s) {
    int r, c, rinc, cinc;
    
    std::shared_ptr<Player> p = std::dynamic_pointer_cast<Player>(s);
    
    if (p) {
        int pos = p->getPosition();
        int numP = board.playersAtPos(pos); // number of players at this tile
        if (numP == 0) numP++;

        if (numP > 4) {
            cinc = (numP-5)*2;
            rinc = 1;
        } else {
            cinc = (numP-1)*2;
            rinc = 0;
        }
        
        if (0 <= pos && pos <= 10) { // Bottom Row
            r = 64 + rinc;
            c = 91 - pos*9 + cinc;
            
        } else if (11 <= pos && pos <= 19) { // Left Side
            r = 64 - (pos-10)*6 + rinc;
            c = 1 + cinc;

        } else if (20 <= pos && pos <= 30) { // Top Row
            r = 4 + rinc;
            c = 1 + (pos-20)*9 + cinc;

        } else { // Right Side
            r = 4 + (pos-30)*6 + rinc;
            c = 91 + cinc;
        }

        if(display[r][c] != ' ') c += 2;
        display[r][c] = p->getPiece();
        printBoard();
        return;
    }

    std::shared_ptr<AcademicBuilding> ab = std::dynamic_pointer_cast<AcademicBuilding>(s);
    if (ab) {
        int loc = ab->getLocation();
        int imps = ab->getImpCount();
        if (0 <= loc && loc <= 10) { // Bottom Row
            r = 61;
            c = 92 - loc*10 + (imps - 1);
            
        } else if (11 <= loc && loc <= 19) { // Left Side
            r = 61 - (loc-10)*6;
            c = 2 + (imps - 1);

        } else if (20 <= loc && loc <= 30) { // Top Row
            r = 1;
            c = 2 + (loc-20)*10 + (imps - 1);

        } else { // Right Side
            r = 1 + (loc-30)*6;
            c = 92 + (imps - 1);

        }

        for (int i = 0; i < 5; i++) {
            if (i < imps) display[r][c+i] = 'I';
            else display[r][c+i] = ' ';
        }
        printBoard();
    }

}

void TextDisplay::cleanPos(const int pos, const char piece) {
    int r, c;
    if (0 <= pos && pos <= 10) { // Bottom Row
        r = 64;
        c = 91 - pos*9;
            
    } else if (11 <= pos && pos <= 19) { // Left Side
        r = 64 - (pos-10)*6;
        c = 1;

    } else if (20 <= pos && pos <= 30) { // Top Row
        r = 4;
        c = 1 + (pos-20)*9;

    } else { // Right Side
        r = 4 + (pos-30)*6;
        c = 91;
    }

    std::vector<char> pOnTile;
    for (int i = 0; i < 8; ++i) {
        if (i < 4) {
            if (display[r][c+2*i] != ' ') {
                if (display[r][c+2*i] == piece) continue;
                pOnTile.emplace_back(display[r][c+2*i]);
                display[r][c+2*i] = ' ';
            } 
        } else {
            if (display[r+1][c+(2*(i-4))] != ' ') {
                if (display[r+1][c+2*(i-4)] == piece) continue;
                pOnTile.emplace_back(display[r+1][c+2*(i-4)]);
                display[r+1][c+(2*(i-4))] = ' ';
            }
        }
    }

    int numP = pOnTile.size();
    for (int i = 0; i < numP; ++i) {
        if (i < 4) {
            display[r][c+2*i] = pOnTile[i]; 
        } else {
            display[r+1][c+(2*(i-4))] = pOnTile[i]; 
        }
    }
}

void TextDisplay::printBoard() const {
    for (auto r : display) {
        for(auto c : r) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}


