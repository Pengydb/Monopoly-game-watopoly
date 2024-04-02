#include "player.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

Player::Player(char piece, const std::string& name, int wallet, School& school, int boardSize, int position, bool visitingTims, 
        int timsLine, int timsCups) : piece(piece), name(name), wallet(wallet), school(school), boardSize(boardSize), position(position), 
                                      visitingTims(visitingTims), timsLine(timsLine), timsCups(timsCups) {
}

int Player::countGym() const{
    return school.countBlocksOwnedBy(name, "Gym");
    // potentially removed and just use the school method instead
}

int Player::countRes() const{
    return school.countBlocksOwnedBy(name, "Residence");
    // potentially removed and just use the school method instead
}

int Player::getWallet() const{
    return wallet;
}

void Player::printAssets() const{
    // still needs to be done, this function may just be moved to school
}

void Player::setWallet(const int amount) {
    wallet = amount;
}

void Player::addWallet(const int amount) {
    // ideally school's transfer funds will be the only palce where this is directly used
    // school should handle the logic of bankruptcy scenarios
    wallet += amount;
}

char Player::getPiece() const{
    return piece;
}

void Player::setPosition(const int pos) {
    position = pos;
}

int Player::getPosition() const {
    return position;
}

int Player::movePosition(const int n) {
    position = (position + n + boardSize) % boardSize;
}

int Player::getTimsLine() const{
    return timsLine;
}

void Player::setTimsLine(const int pos) {
    timsLine = pos;
}

bool Player::isVisitingTims() const {
    return visitingTims;
}

void Player::toggleVisiting() {
    visitingTims = !visitingTims;
}

int Player::getTimsCups() const {
    return timsCups;
}

void Player::addTimsCups(const int n) {
    timsCups += n;
}

std::string Player::getName() const{
    return name;
}

/**
void Player::notEnoughCash(School &s) {
    int assets = s.getLiquidAssets(this->getName());
    if (this->getWallet() < 0) {
        std::cout << "You do not have enough cash to pay the fee" << std::endl;
        if (assets + this->getWallet() < 0) {
            std::cout << "You do not have enough assets to pay the fee, you are BANKRUPT" << std::endl;
            s.declareBankrupcy(this->getName());
            return;
        }
        std::cout << "To get enough cash you will have to sell improvements or mortage your properties." << std::endl;
        std::cout << "Enter: \"sell <property> n\" to sell n improvements on <property>" << std::endl;
        std::cout << "Enter: \"mortgage <property> \" to mortagage <property>";
        std::cout << " (Note that all improvements on <property> will be sold before it gets mortgaged)" << std::endl;
        while(true) { // Can pay if they sell assets
            std::string cmd, prop;
            std::cin >> cmd >> prop;
            /*if (!s.isOwner(p.getName(), prop)) {
                cout << "You do not own this property" << endl;
                continue;
            }*/
            /*
            if (cmd == "improve") { // chose to sell improvements
                int imps;
                std::cin >> imps; // Should add checking to make sure imps is an integer > 0
                s.sellImprovement(prop, imps);
            } else if (cmd == "mortgage") { // chose to mortgage property
                s.mortgageProperty(prop);
            } 

            if (this->getWallet() < 0) {
                std::cout << "You still don't have enough to pay fee, mortgage or sell improvements" << std::endl;
            } else {
                break;
            }
        } // while
    } // if
}
*/

int roll() {
    std::vector<int> die{1, 2, 3, 4, 5, 6}; 
    std::random_device rd;
    std::mt19937 seed(rd());
    std::shuffle(die.begin(), die.end(), seed); // Shuffles elements in die
    return die[0];
}