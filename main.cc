#include "board.h"
#include "player.h"
#include "tile.h"
#include "textdisplay.h"
#include "bank.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::shared_ptr<Board> board = std::make_shared<Board>();
    bool isTesting = false;
    if (argc > 1) {
    std::string command = argv[1];
        if (command == "-load") {
            std::string filename = argv[2];
            board->loadGame(filename, "TileOrder.csv", "propertyconfig.csv");
            board->playGame(false, isTesting);
        }
        else if(command == "-testing") {
            isTesting = true;
        }
    }
    else {

        std::cout << "Watopoly: The Univeristy of Waterloo Monopoly!" << std::endl;
        std::cout << "Enter one of the following commands to start playing: \n"
                  << "start - starts a new game \n"
                  << "load <file.txt> - loads a saved game from file.txt \n"
                  << "exit - to exit the program \n"
                  << std::endl;

        std::string cmd;
        std::cin >> cmd;

        if (cmd == "start") {
            board->setupBoard("TileOrder.csv", "propertyconfig.csv");
            board->playGame(true, isTesting);
        }
        else if (cmd == "load") {
            std::cout << "Please enter the name of the file to be loaded including its extension" << std::endl;
            std::string loadFile;
            std::getline(std::cin, loadFile);
            board->loadGame(loadFile, "TileOrder.csv", "propertyconfig.csv");
        }
        else if (cmd == "exit") {
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}