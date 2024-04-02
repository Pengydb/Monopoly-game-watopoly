#include "board.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// void Board::saveGame() 

int Board::getTurn() {
    return playerTurn;
}

void Board::startGame() {
    shared_ptr<AcademicBuilding> AL = nullptr;
    shared_ptr<AcademicBuilding> ML = nullptr;
    shared_ptr<AcademicBuilding> ECH = nullptr;
    shared_ptr<AcademicBuilding> PAS = nullptr;
    shared_ptr<AcademicBuilding> HH = nullptr;
    shared_ptr<AcademicBuilding> RCH = nullptr;
    shared_ptr<AcademicBuilding> DWE = nullptr;
    shared_ptr<AcademicBuilding> CPH = nullptr;
    shared_ptr<AcademicBuilding> LHI = nullptr;
    shared_ptr<AcademicBuilding> BMH = nullptr;
    shared_ptr<AcademicBuilding> OPT = nullptr;
    shared_ptr<AcademicBuilding> EV1 = nullptr;
    shared_ptr<AcademicBuilding> EV2 = nullptr;
    shared_ptr<AcademicBuilding> EV3 = nullptr;
    shared_ptr<AcademicBuilding> PHYS = nullptr;
    shared_ptr<AcademicBuilding> B1 = nullptr;
    shared_ptr<AcademicBuilding> B2 = nullptr;
    shared_ptr<AcademicBuilding> EIT = nullptr;
    shared_ptr<AcademicBuilding> ESC = nullptr;
    shared_ptr<AcademicBuilding> C2 = nullptr;
    shared_ptr<AcademicBuilding> MC = nullptr;
    shared_ptr<AcademicBuilding> DC = nullptr;

    shared_ptr<Residence> MKV = nullptr;
    shared_ptr<Residence> UWP = nullptr;
    shared_ptr<Residence> V1 = nullptr;
    shared_ptr<Residence> REV = nullptr;

    shared_ptr<Gym> PAC = nullptr;
    shared_ptr<Gym> CIF = nullptr;

    shared_ptr<NonOwnableProperty> OSAP = nullptr;
    shared_ptr<NonOwnableProperty> DCTims = nullptr;
    shared_ptr<NonOwnableProperty> GoToTims = nullptr;
    shared_ptr<NonOwnableProperty> GooseNesting = nullptr;
    shared_ptr<NonOwnableProperty> Tuition = nullptr;
    shared_ptr<NonOwnableProperty> CoopFee = nullptr;
    shared_ptr<NonOwnableProperty> SLC = nullptr;
    shared_ptr<NonOwnableProperty> NH = nullptr;

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

    string playerPiece;
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
        getline(cin, playerPiece);
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
    School school;
    shared_ptr<Player> name = make_shared<Player>(playerPiece, name, 1500, school, 49)
    cout << "Player " << name << " added" << endl;
}

void Board::movePlayer(Player &p, Tile &t) {
    player.setPosition(tile.getLocation());
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
