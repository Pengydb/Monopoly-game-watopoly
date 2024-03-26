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
    buildings = vector<Tile*>(40, nullptr);
    buildings[0] = new collectOSAP();
    buildings[1] = new AcademicBuilding("AL", 1, 40, 2, false, false, 0, 50, MonopolyBlock::Arts1);
    // AcademicBuilding(const string& name, int location, int cost, int fee, bool owned, bool mortgaged, int impCount, int impCost, MonopolyBlock block)
    // Assuming fee is the Tuition paid when a player lands on the tile without any improvements
    buildings[2] = new SLC(2);
    // Since there are 3 SLC tiles, SLC(int location);
    buildings[3] = new AcademicBuilding("ML", 3, 60, 4, false, false, 0, 50, MonopolyBlock::Arts1);
    buildings[4] = new tuition();
    buildings[5] = new Residence("MKV", 5, 200, 25, false, false);
    // Residence(const string& name, int location, int cost, int fee, bool owned, bool mortgaged)
    // In this case fee is the rent paid depending on the number of residences owned
    buildings[6] = new AcademicBuilding("ECH", 6, 100, 6, false, false, 0, 50, MonopolyBlock::Arts2);
    buildings[7] = new NH(7);
    // Since there are 3 Needles Hall tiles, NH(int location);
    buildings[8] = new AcademicBuilding("PAS", 8, 100, 6, false, false, 0, 50, MonopolyBlock::Arts2);
    buildings[9] = new AcademicBuilding("HH", 9, 120, 8, false, false, 0, 50, MonopolyBlock::Arts2);
    buildings[10] = new dcTims();
    buildings[11] = new AcademicBuilding("RCH", 11, 140, 10, false, false, 0, 100, MonopolyBlock::Eng);
    buildings[12] = new Gym("PAC", 12, 150, 0, false, false, 0);
    // Gym(const string& name, int location, int cost, int fee, bool owned, bool mortgaged, int multiplier)
    // in this case fee is initialized to 0 because it depends on the dice roll
    // initially the multiplier is 0 because no one has owned it yet
    buildings[13] = new AcademicBuilding("DWE", 13, 140, 10, false, false, 0, 100, MonopolyBlock::Eng);
    buildings[14] = new AcademicBuilding("CPH", 14, 160, 12, false, false, 0, 100, MonopolyBlock::Eng);
    buildings[15] = new Residence("UWP", 15, 200, 25, false, false);
    buildings[16] = new AcademicBuilding("LHI", 16, 180, 14, false, false, 0, 100, MonopolyBlock::Health);
    buildings[17] = new SLC(17);
    buildings[18] = new AcademicBuilding("BMH", 18, 180, 14, false, false, 0, 100, MonopolyBlock::Health);
    buildings[19] = new AcademicBuilding("OPT", 19, 200, 16, false, false, 0, 100, MonopolyBlock::Health);
    buildings[20] = new gooseNesting();
    buildings[21] = new AcademicBuilding("EV1", 21, 220, 18, false, false, 0, 150, MonopolyBlock::Env);
    buildings[22] = new NH(22);
    buildings[23] = new AcademicBuilding("EV2", 23, 220, 18, false, false, 0, 150, MonopolyBlock::Env);
    buildings[24] = new AcademicBuilding("EV3", 24, 240, 20, false, false, 0, 150, MonopolyBlock::Env);
    buildings[25] = new Residence("V1", 25, 200, 25, false, false);
    buildings[26] = new AcademicBuilding("Phys", 26, 260, 22, false, false, 0, 150, MonopolyBlock::Sci1);
    buildings[27] = new AcademicBuilding("B1", 26, 260, 22, false, false, 0, 150, MonopolyBlock::Sci1);
    buildings[28] = new Gym("PAC", 28, 150, 0, false, false, 0);
    buildings[29] = new AcademicBuilding("B2", 29, 280, 24, false, false, 0, 150, MonopolyBlock::Sci1);
    buildings[30] = new goToTims();
    buildings[31] = new AcademicBuilding("EIT", 31, 300, 26, false, false, 0, 200, MonopolyBlock::Sci2);
    buildings[32] = new AcademicBuilding("ESC", 32, 300, 26, false, false, 0, 200, MonopolyBlock::Sci2);
    buildings[33] = new SLC(33);
    buildings[34] = new AcademicBuilding("C2", 34, 320, 28, false, false, 0, 200, MonopolyBlock::Sci2);
    buildings[35] = new Residence("REV", 35, 200, 25, false, false);
    buildings[36] = new NH();
    buildings[37] = new AcademicBuilding("MC", 37, 350, 35, false, false, 0, 200, MonopolyBlock::Math);
    buildings[38] = new coopFee();
    buildings[39] = new AcademicBuilding("DC", 37, 400, 50, false, false, 0, 200, MonopolyBlock::Math);


    cout << "Enter the number of players: " << endl;;
    int numPlayers;
    cin >> numPlayers;
    cin.ignore();

    for (int i = 0; i < numPlayers; ++i) {
        setPlayer();
    }
        playerTurn = 0;
        cout << "Game started with " << numPlayers << " players." << endl;


        // Check how to update the property ownership array
}

void Board::setPlayer() {
    cout << "Enter player's name: ";
    string name;
    getline(cin, name);
    cin.ignore();

    map<string, PlayerPiece> pieceMap = { // Mapping each string to a PlayerPiece
        {"Goose", PlayerPiece::Goose},
        {"GRTBus", PlayerPiece::GRTBus},
        {"TimHortonsDoughnut", PlayerPiece::TimHortonsDoughnut},
        {"Professor", PlayerPiece::Professor},
        {"Student", PlayerPiece::Student},
        {"Money", PlayerPiece::Money},
        {"Laptop", PlayerPiece::Laptop},
        {"PinkTie", PlayerPiece::PinkTie}
    };

    string input;
    PlayerPiece piece;
    while (1) {
        cout << "Enter player's piece out of:\n"
             << "Goose\n"
             << "GRTBus\n"
             << "TimHortonsDoughnut\n"
             << "Professor\n"
             << "Student\n"
             << "Money\n"
             << "Laptop\n"
             << "PinkTie"; << endl;
        getline(cin, input);
        if (pieceMap.find(input) != pieceMap.end()) {
            piece = pieceMap[input];
            cout << "You chose the " << input << " piece." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } ;

    Player* newPlayer = new Player(name, piece, 1500, 0, false, false, 0); // considering the constructor for Player is as follows: 
    //Player(name, PlayerPiece, wallet, position, isBankrupt, visitingTims, timsLine) and considering the position of CollectOSAP is 0
    players.push_back(newPlayer);
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
