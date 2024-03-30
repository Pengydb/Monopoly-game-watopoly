#ifndef _NONOWNABLEPROPERTY_H_
#define _NONOWNABLEPROPERTY_H_

#include "tile.h"

class NonOwnableProperty : public Tile {
  public:
    virtual void performAction(Player &p) = 0;
};


class CollectOsap : public NonOwnableProperty {
  public:
    void performAction(Player &p) override; 
};

class DCTims : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class GoToTims : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class GooseNesting : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class Tuition : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class CoopFee : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class SLC : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

class NH : public NonOwnableProperty {
  public:
    void performAction(Player &p) override;
};

#endif // NONOWNABLEPROPERTY_H
