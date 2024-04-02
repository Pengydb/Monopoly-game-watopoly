#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// void Board::saveGame() 

int Board::getTurn() {
    return playerTurn;
}

void Board::startGame(const std::string &filename)
{
    
    std::ifstream file(filename);
    std::vector<std::shared_ptr<OwnableProperty>> AcademicBuildings;

    std::string line;
    while (getline(file, line))
    {
        std::string buildingType, buildingName;
        std::istringstream iss(line);
        std::getline(iss, buildingType, ',');
        std::getline(iss, buildingName);

        if (buildingType == "AB")
        {
            std::shared_ptr<AcademicBuilding> tile = nullptr;
            buildings.push_back(tile);
            AcademicBuildings.push_back(tile);
        }
        else if (buildingType == "R")
        {
            std::shared_ptr<Residence> tile = nullptr;
            buildings.push_back(tile);
        }
        else if (buildingType == "GYM")
        {
            std::shared_ptr<Gym> tile = nullptr;
            buildings.push_back(tile);
        }
        else if (buildingType == "NOP")
        {
            std::shared_ptr<NonOwnableProperty> tile = nullptr;
            buildings.push_back(tile);
        }
    }
    file.close();

    std::cout << "Enter the number of players: " << std::endl;
    int numPlayers;
    std::cin >> numPlayers;
    std::cin.ignore();

    for (int i = 0; i < numPlayers; ++i) {
        std::shared_ptr<Player> player = setPlayer();
        players.push_back(player);
    }
    school = make_shared<School>(players, AcademicBuildings, 43);
    playerTurn = 0;
    std::cout << "Game started with " << numPlayers << " players." << endl;
}

std::shared_ptr<Player> Board::setPlayer()
{
    std::string name;
    while(true){
        std::cout << "Enter player's name: " << std::endl;
        std::getline(std::cin, name);
        if (!name.empty()){
            break;
        }
        else{
            std::cout << "Invalid name. Player not added." << std::endl;
        }
    }

    char playerPiece;
    while (true) {
        std::cout << "Enter player's piece out of:\n"
                  << "G (Goose)\n"
                  << "B (GRTBus)\n"
                  << "D (TimHortonsDoughnut)\n"
                  << "P (Professor)\n"
                  << "S (Student)\n"
                  << "$ (Money)\n"
                  << "L (Laptop)\n"
                  << "T (PinkTie)" << std::endl;
        std::cin >> playerPiece;
        switch(playerPiece) {
        case 'G':
        case 'B':
        case 'D':
        case 'P':
        case 'S':
        case '$':
        case 'L':
        case 'T':
            std::cout << "You chose the " << playerPiece << " piece." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            continue;
        }
        break;
    };
    const int wallet = 1500;
    const int boardSize = 49;
    std::shared_ptr<Player> player = make_shared<Player>(playerPiece, name, wallet, *school, boardSize);
    return player;
}

void Board::movePlayer(Player &p, int roll) {
    int index = p.getPosition();
    index = (index + roll) % 50;
    p.setPosition(index);
}

void Board::removePlayer(Player &player)
{
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        if (it->get() == &player)
        {
            players.erase(it);
            break;
        }
    }
}

void Board::nextTurn() {
    playerTurn = (playerTurn + 1) % (players.size() + 1);
}

//void Board::printBoard() {}
