#include "player.h"
#include <stdexcept>

Player::Player(char piece, const std::string& name, int wallet, School& school, int boardSize, int position, bool visitingTims, 
        int timsLine, int timsCups) : piece(piece), name(name), wallet(wallet), school(school), boardSize(boardSize), position(position), 
                                      visitingTims(visitingTims), timsLine(timsLine), timsCups(timsCups) {
}

int Player::countGym() const{
    return school.countGymsOwnedBy(*this);
    // potentially removed and just use the school method instead
}

int Player::countGym() const{
    return school.countResOwnedBy(*this);
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
