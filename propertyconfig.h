#ifndef __PROPERTYCONFIG_H_
#define __PROPERTYCONFIG_H_

#include <vector>
#include <string>

class PropertyConfig {
private:
    // Stores the name of the property
    std::string name;
    // Stores the monopoly group the property belongs to
    std::string group;
    // Stores the cost of buying
    int buyingCost;
    // Stores the cost of improving
    int impCost;
    // Stores the fee depending on the number of improvements
    // Indexed by stage of improvement, starting from base 0
    std::vector<int> fees;
    
public:
    // Constructor to initialize all necessary fields
    PropertyConfig(const std::string& name, const std::string& group, int buyingCost, int impCost, const std::vector<int>& rents);

    // Creates a PropertyConfig from a CSV string
    static PropertyConfig fromCSV(const std::string& csvLine);
    // Sets the name of the property
    void setName(const std::string& newName);
    // Returns the name of the property
    std::string getName() const;
    // Sets which monopoly group the property belongs to
    void setGroup(const std::string& newGroup);
    // Returns the monopoly group for which the property belongs to
    std::string getGroup() const;
    // Sets the buying cost of the property
    void setCost(const int newCost);
    // Returns the buying cost of the property
    int getCost() const;
    // Sets the cost of adding improvements
    void setImpCost(const int newImpCost);
    // Returns the cost of adding improvements
    int getImpCost() const;
    // Returns fee based on stage of improvement
    int getFee(int stage) const;
};

#endif // PROPERTYCONFIG_H
