#include "board.h"
#include "player.h"
#include "tile.h"
#include "textdisplay.h"
#include "bank.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::string filename;
    bool isTesting = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-load") {
            if (i + 1 < argc) {
                std::string nextArg = argv[i+1];
            
                if(!nextArg.empty() && nextArg[0] != '-') {
                    filename = nextArg;
                    ++i;
                } 
            }
            else {
                std::cout << "Error: -load must be followed by a filename." << std::endl;
                return 1;
            } 
        } else if (arg == "-testing") {
                isTesting = true;
        }
    }
        
    if (!filename.empty()) {
        board->loadGame(filename, "TileOrder.csv", "propertyconfig.csv");
        board->playGame(false, isTesting);
    }
        
    else {
        std::cout << "Watopoly: The Univeristy of Waterloo Monopoly!" << std::endl;
        std::cout << "Enter one of the following commands to start playing: \n"
                  << "start - starts a new game \n"
                //  << "load <file.txt> - loads a saved game from file.txt \n"
                  << "exit - to exit the program \n"
                  << std::endl;

        std::string cmd;
        std::cin >> cmd;

        if (cmd == "start") {
            board->setupBoard("TileOrder.csv", "propertyconfig.csv");
            board->playGame(true, isTesting);
        }
        /*else if (cmd == "load") {
            std::cout << "Please enter the name of the file to be loaded including its extension" << std::endl;
            std::string loadFile;
            std::getline(std::cin, loadFile);
            board->loadGame(loadFile, "TileOrder.csv", "propertyconfig.csv");
        }*/

        else if (cmd == "exit") {
            return 0;
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}