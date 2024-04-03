#include "board.h"
#include "player.h"
#include "tile.h"
#include "textdisplay.h"
#include "bank.h"
#include <iostream>
#include <string>


int main() {
    std::cout << "Watopoly: The Univeristy of Waterloo Monopoly!" << std::endl;
    std::cout << "Enter one of the following commands to start playing: \n"
              << "start - starts a new game \n"
              << "load <file.txt> - loads a saved game from file.txt \n"
              << "exit - to exit the program \n" << std::endl;

    std::string cmd;
    std::cin >> cmd;

    if (cmd == "start") {

    } else if (cmd == "load") {

    } else if (cmd == "exit") {

    } else {
        std::cout << "Unknown command" << std::endl;
    }
}