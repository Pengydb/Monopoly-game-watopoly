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
    std::vector<int> rents; // Indexed by stage of imrpovement, starting from base
    
public:
    PropertyConfig(const std::string& name, const std::string& group, int buyingCost, int impCost, const std::vector<int>& rents);

    void setName(const std::string& name);
    std::string getName() const;

    void setGroup(const std::string& group);
    std::string getGroup() const;

    void setCost(const int cost);
    int getCost() const;

    void setImpCost(const int impCost);
    int getImpCost() const;

    int getRent(int stage) const;
};

#endif 
