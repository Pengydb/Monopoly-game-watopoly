#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// void Board::saveGame() 

int Board::getTurn() {
    return playerTurn;
}

void Board::startGame(const std::string &filename)
{
    
    std::ifstream file(filename);
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Tile>> AcademicBuildings;

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
            tiles.push_back(tile);
            AcademicBuildings.push_back(tile);
        }
        else if (buildingType == "R")
        {
            std::shared_ptr<Residence> tile = nullptr;
            tiles.push_back(tile);
        }
        else if (buildingType == "GYM")
        {
            std::shared_ptr<Gym> tile = nullptr;
            tiles.push_back(tile);
        }
        else if (buildingType == "NOP")
        {
            std::shared_ptr<NonOwnableProperty> tile = nullptr;
            tiles.push_back(tile);
        }
    }
    file.close();
    

    cout << "Enter the number of players: " << endl;;
    int numPlayers;
    cin >> numPlayers;
    cin.ignore();

    for (int i = 0; i < numPlayers; ++i) {
        setPlayer();
    }
        playerTurn = 0;
        cout << "Game started with " << numPlayers << " players." << endl;
}

void Board::setPlayer() {
    string name;
    while(true){
        cout << "Enter player's name: " << endl;
        getline(cin, name);
        if (!name.empty()){
            break;
        }
        else{
            cout << "Invalid name. Player not added." << endl;
        }
    }

    char playerPiece;
    while (true) {
        cout << "Enter player's piece out of:\n"
             << "G (Goose)\n"
             << "B (GRTBus)\n"
             << "D (TimHortonsDoughnut)\n"
             << "P (Professor)\n"
             << "S (Student)\n"
             << "$ (Money)\n"
             << "L (Laptop)\n"
             << "T (PinkTie)" << endl;
        cin >> playerPiece;
        switch(playerPiece) {
        case 'G':
        case 'B':
        case 'D':
        case 'P':
        case 'S':
        case '$':
        case 'L':
        case 'T':
            cout << "You chose the " << playerPiece << " piece." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
        break;
    };
    shared_ptr<School> school = nullptr;
    const int wallet = 1500;
    const int boardSize = 49;
    shared_ptr<Player> name = make_shared<Player>(playerPiece, name, wallet, school, boardSize);
    cout << "Player " << name << " added" << endl;
}

void Board::movePlayer(Player &p, Tile &t) {
    p.setPosition(t.getLocation());
}

void Board::removePlayer(Player &player) {
    for (auto it = players.begin(); it != players.end(); ++it) {
        if (*it == &player) {
            players.erase(it);
            break;
        }
    }
}

void Board::nextTurn() {
    playerTurn = (playerTurn + 1) % players.size();
}

//void Board::playGame() {}       What is the difference between next turn and play game

//void Board::printBoard() {}     What is the purpose of the TextDisplay class?
