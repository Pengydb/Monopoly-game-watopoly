#include "propertyconfig.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

PropertyConfig::PropertyConfig(const std::string& name, const std::string& group, int buyingCost, int impCost, const std::vector<int>& fees)
    : name(name), group(group), buyingCost(buyingCost), impCost(impCost), fees(fees) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }
    if (group.empty()) {
        throw std::invalid_argument("Group cannot be empty.");
    }
    if (buyingCost < 0) {
        throw std::invalid_argument("Buying cost cannot be negative.");
    }
    if (impCost < 0) {
        throw std::invalid_argument("Improvement cost cannot be negative.");
    }
    if (fees.empty()) {
        throw std::invalid_argument("At least one fee stage must be provided.");
    }
    for (auto fee : fees) {
        if (fee < 0) {
            throw std::invalid_argument("Fees cannot be negative.");
        }
    }
}

void removeWhitespace(std::string &str)
{
    // Remove leading whitespace and quotation marks
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c)
                                        { return !std::isspace(c) && c != '"'; }));

    // Remove trailing whitespace and quotation marks
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c)
                           { return !std::isspace(c) && c != '"'; })
                  .base(),
              str.end());
}

PropertyConfig PropertyConfig::fromCSV(const std::string& csvLine) {
    std::istringstream readLine(csvLine);
    std::string readValue, name, group;
    int buyingCost, impCost;
    std::vector<int> fees;
    std::getline(readLine, readValue, ',');

    std::getline(readLine, readValue, ',');
    removeWhitespace(readValue);
    name = readValue;

    std::getline(readLine, readValue, ',');
    removeWhitespace(readValue);
    group = readValue;
    
    std::getline(readLine, readValue, ',');
    removeWhitespace(readValue);
    buyingCost = std::stoi(readValue);

    std::getline(readLine, readValue, ',');
    removeWhitespace(readValue);
    impCost = std::stoi(readValue);

    while (std::getline(readLine, readValue, ',')) {
        fees.emplace_back(std::stoi(readValue));
    }

    return PropertyConfig(name, group, buyingCost, impCost, fees);
}

// Setters
void PropertyConfig::setName(const std::string& newName) {
    name = newName;
}

void PropertyConfig::setGroup(const std::string& newGroup) {
    group = newGroup;
}

void PropertyConfig::setCost(const int newCost) {
    if (newCost < 0) {
        throw std::invalid_argument("Buying Cost cannot be negative.");
    }
    buyingCost = newCost;
}

void PropertyConfig::setImpCost(const int newImpCost) {
    if (newImpCost < 0) {
        throw std::invalid_argument("Improvement Cost cannot be negative");
    }
    impCost = newImpCost;
}

// Getters
std::string PropertyConfig::getName() const {
    return name;
}

std::string PropertyConfig::getGroup() const {
    return group;
}

int PropertyConfig::getCost() const {
    return buyingCost;
}

int PropertyConfig::getImpCost() const {
    return impCost;
}

// Get the rent at a specific improvement stage
int PropertyConfig::getFee(int stage) const {
    if (stage < 0 || stage >= fees.size()) {
        throw std::out_of_range("Invalid stage for retrieval");
    }
    return fees[stage];
}
