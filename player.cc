#include "player.h"
#include "ownableproperty.h"
#include "bank.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

Player::Player(char piece, const std::string& name, int wallet, Bank& bank, int boardSize, int position, bool visitingTims, 
        int timsLine, int timsCups, int gyms, int res, bool buy, bool pay, int fee, std::string feeOwner) : 
        piece(piece), name(name), wallet(wallet), bank(bank), boardSize(boardSize), position(position), 
        visitingTims(visitingTims), timsLine(timsLine), timsCups(timsCups), gyms(gyms), res(res), 
        buy(buy), pay(pay), fee(fee), feeOwner(feeOwner) {}


int Player::getWallet() const { return wallet; }

void Player::setWallet(const int amount) { wallet = amount; }

// ideally bank's transfer funds will be the only place where this is directly used
// bank should handle the logic of bankruptcy scenarios
void Player::addWallet(const int amount) { wallet += amount; }

char Player::getPiece() const { return piece; }

void Player::setPosition(const int pos) { position = pos; }

int Player::getPosition() const { return position; }

int Player::movePosition(const int n) {
    position = (position + n + boardSize) % boardSize;
    this->notifyObservers();
}

int Player::getTimsLine() const { return timsLine; }

void Player::setTimsLine(const int n) { timsLine = n; }

bool Player::isVisitingTims() const { return visitingTims; }

void Player::toggleVisiting() { visitingTims = !visitingTims; }

int Player::getTimsCups() const { return timsCups; }

void Player::addTimsCups(const int n) { timsCups += n; }

std::string Player::getName() const{ return name; }

int Player::getGyms() const { return gyms; }

int Player::getRes() const { return res; }

void Player::addGyms(const int n) { gyms + n; }

void Player::addRes(const int n) { res + n; }

bool Player::canBuy() const { return buy; }

bool Player::hasToPay() const { return pay; }

void Player::toggleCanBuy() { buy = !(buy); }

void Player::toggleHasToPay() { pay = !(pay); }

int Player::getFee() const { return fee; }

void Player::setFee(const int n) { fee = n; }

void Player::setFeeOwner(std::string owner) { feeOwner = owner; }

std::string Player::getFeeOwner() const { return feeOwner; }

int Player::roll() const {
    std::vector<int> die{1, 2, 3, 4, 5, 6}; 
    std::random_device rd;
    std::mt19937 seed(rd());
    std::shuffle(die.begin(), die.end(), seed); // Shuffles elements in die
    return die[0];
}

