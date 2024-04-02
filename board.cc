#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void Board::saveGame() {
    std::string filename = "savegame.txt";
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("Error opening file " + filename);
    }

    for (const auto &player : players)
    {
        file << "Player: " << player->getName() << "," << player->getPiece() << "," << player->getWallet() << "," << player->getPosition() << "," << player->isVisitingTims() << "," << player->getTimsLine() << "," << player->getTimsCups() << std::endl;
    }

    for (const auto &tile : buildings)
    {
        if (auto ab = std::dynamic_pointer_cast<AcademicBuilding>(tile))
        {
            if (ab->isOwned()){
                file << "AcademicBuilding: " << ab->getName() << "," << school->getPropertyOwner(ab->getName()) << "," << ab->isMortgaged() << "," << ab->getImpCount() << "," << ab->getImpCost() << std::endl;
            }
            else {
                file << "AcademicBuilding: " << ab->getName() << "," << "false" << "," << ab->isMortgaged() << "," << ab->getImpCount() << "," << ab->getImpCost() << std::endl;
            }
        }
        else if (auto r = std::dynamic_pointer_cast<Residence>(tile))
        {
            if (r->isOwned()){
                file << "Residence: " << r->getName() << "," << school->getPropertyOwner(r->getName()) << "," << r->isMortgaged() << std::endl;
            }
            else {
                file << "Residence: " << r->getName() << "," << "false" << "," << r->isMortgaged() << std::endl;
            }
            
        }
        else if (auto g = std::dynamic_pointer_cast<Gym>(tile))
        {
            if (g->isOwned())
            {
                file << "Gym: " << g->getName() << "," << school->getPropertyOwner(g->getName()) << "," << g->isMortgaged() << std::endl;
            }
            else
            {
                file << "Gym: " << g->getName() << "," << "false" << "," << g->isMortgaged() << std::endl;
            }
        }
        else
        {
            throw std::invalid_argument("Unknown tile type.");
        }
        
    }

    file << "Current turn:" << playerTurn << std::endl;
    file.close();
    std::cout << "Game saved to " << filename << std::endl;
}


void Board::loadGame(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("Error opening file " + filename);
    }

    players.clear();
    buildings.clear();
    playerTurn = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ':');
        if (token == "Player")
        {
            std::string name, piece;
            int wallet, position, timsLine, timsCups;
            bool visitingTims;
            std::getline(ss, name, ',');
            std::getline(ss, piece, ',');
            ss >> wallet;
            ss.ignore();
            ss >> position;
            ss.ignore();
            ss >> visitingTims;
            ss.ignore();
            ss >> timsLine;
            ss.ignore();
            ss >> timsCups;
            ss.ignore();
            const int boardSize = 49;
            auto player = std::make_shared<Player>(piece[0], name, wallet, boardSize, *school, boardSize, position, visitingTims, timsLine, timsCups);
            players.push_back(player);
        }
        else if (token == "AcademicBuilding")
        {
            std::string name, ownerStr, isMortgagedStr;
            int impCount, impCost;
            bool isMortgaged, isOwned;
            std::getline(ss, name, ',');
            std::getline(ss, ownerStr, ',');
            std::getline(ss, isMortgagedStr, ',');
            ss >> impCount;
            ss.ignore();
            ss >> impCost;
            ss.ignore();

            isMortgaged = (isMortgagedStr == "true");
            isOwned = (ownerStr != "false");
            auto academicBuilding = std::make_shared<AcademicBuilding>(name, isOwned, isMortgaged, impCount, impCost);
            if (isOwned){
                school->addPropertyOwner(name, ownerStr);
            }
            buildings.push_back(academicBuilding);
        }
        else if (token == "Residence")
        {
            std::string name, ownerStr, isMortgagedStr;
            bool isMortgaged, isOwned;
            std::getline(ss, name, ',');
            std::getline(ss, ownerStr, ',');
            std::getline(ss, isMortgagedStr, ',');

            isMortgaged = (isMortgagedStr == "true");
            isOwned = (ownerStr != "false");
            auto residence = std::make_shared<Residence>(name, isOwned, isMortgaged);
            buildings.push_back(residence);
        }
        else if (token == "Gym")
        {
            std::string name, ownerStr, isMortgagedStr;
            bool isMortgaged, isOwned;
            std::getline(ss, name, ',');
            std::getline(ss, ownerStr, ',');
            std::getline(ss, isMortgagedStr, ',');

            isMortgaged = (isMortgagedStr == "true");
            isOwned = (ownerStr != "false");
            auto gym = std::make_shared<Gym>(name, isOwned, isMortgaged);
            buildings.push_back(gym);
        }
        else if (token == "Current turn")
        {
            ss >> playerTurn;
            ss.ignore();
        }
        else
        {
            throw std::invalid_argument("Unknown token: " + token);
        }
    }
    file.close();
}


int Board::getTurn() {
    return playerTurn;
}

void Board::startGame(const std::string &filename)
{
    
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::invalid_argument("Error opening file " + filename);
    }
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
        else
        {
            throw std::invalid_argument("Unknown building type: " + buildingType);
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

    const int cards = 15;
    school = make_shared<School>(players, AcademicBuildings, cards);
    playerTurn = 0;
    std::cout << "Game started with " << numPlayers << " players." << std::endl;
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
            throw std::invalid_argument("Invalid name. Player not added.");
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
            throw std::invalid_argument("Invalid choice. Please try again.");
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

// void Board::notify(Subject &s){
//     for (auto &observer : observers)
//     {
//         observer->update(s);
//     }
// }

//void Board::printBoard() {}


std::string Board::getTileName(const int n) const {
    return buildings[n]->getName();
}