#ifndef __PROPERTYCONFIG_H_
#define __PROPERTYCONFIG_H_

#include <vector>
#include <string>

class PropertyConfig {
private:
    std::string name;
    std::string group;
    int buyingCost;
    int impCost;
    std::vector<int> fees; // Indexed by stage of improvement, starting from base 0
    
public:
    PropertyConfig(const std::string& name, const std::string& group, int buyingCost, int impCost, const std::vector<int>& rents);

    // Creates a PropertyConfig from a CSV string
    static PropertyConfig fromCSV(const std::string& csvLine);

    void setName(const std::string& newName);
    std::string getName() const;

    void setGroup(const std::string& newGroup);
    std::string getGroup() const;

    void setCost(const int newCost);
    int getCost() const;

    void setImpCost(const int newImpCost);
    int getImpCost() const;

    // Returns fee based on stage of improvement
    int getFee(int stage) const;
};

#endif // PROPERTYCONFIG_H
