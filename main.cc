#include "board.h"
#include "player.h"
#include "tile.h"
#include "textdisplay.h"
#include "bank.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::string command = argv[1];
    if (command == "-load")
    {
        std::string filename = argv[2];
        board->loadGame(filename);
        board->loadGame(argv[2]);
    }
    else if(command == "-testing"){
        
    }

        std::cout << "Watopoly: The Univeristy of Waterloo Monopoly!" << std::endl;
        std::cout << "Enter one of the following commands to start playing: \n"
                  << "start - starts a new game \n"
                  << "load <file.txt> - loads a saved game from file.txt \n"
                  << "exit - to exit the program \n"
                  << std::endl;

        std::string cmd;
        std::cin >> cmd;

        if (cmd == "start")
        {
        }
        else if (cmd == "load")
        {
        }
        else if (cmd == "exit")
        {
        }
        else
        {
            std::cout << "Unknown command" << std::endl;
        }
    }