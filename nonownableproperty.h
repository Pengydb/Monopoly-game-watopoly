#ifndef _NONOWNABLEPROPERTY_H_
#define _NONOWNABLEPROPERTY_H_

#include "tile.h"
#include "school.h"


class NonOwnableProperty : public Tile {
  public:
    virtual void performAction(Player &p, School &s) = 0;
};


class CollectOsap : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override; 
};

class DCTims : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class GoToTims : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class GooseNesting : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class Tuition : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class CoopFee : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class SLC : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

class NH : public NonOwnableProperty {
  public:
    void performAction(Player &p, School &s) override;
};

#endif // NONOWNABLEPROPERTY_H
