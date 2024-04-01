#ifndef __PROPERTYENHANCEMENT_H_
#define __PROPERTYENHANCEMENT_H_

#include "ownableproperty.h"
#include <memory>
class PropertyEnhancement: public OwnableProperty {
protected:
    std::shared_ptr<OwnableProperty> property; // Points to base property

public:
    explicit PropertyEnhancement(std::shared_ptr<OwnableProperty> property): OwnableProperty(property->getConfig()), property(property) {}
    virtual ~PropertyEnhancement() = default;

    virtual std::shared_ptr<OwnableProperty> removeDecorator() { return property;}

    bool isPropertyEnhancement() const override { return true; }

    int getDepth() const override {
        return 1 + property->getDepth();
    }

    int getFee() const override {
        return property->getConfig().getFee(getDepth());
    }

};

#endif
