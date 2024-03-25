#ifndef _NONOWNABLEPROPERTY_H_
#define _NONOWNABLEPROPERTY_H_

#include "tile.h"

class NonOwnableProperty : public Tile {
  public:
    virtual void performAction() = 0;
};


class CollectOsap : public NonOwnableProperty {
  public:
    void performAction() override; 
};

class DCTims : public NonOwnableProperty {
  public:
    void performAction() override;
};

class GoToTims : public NonOwnableProperty {
  public:
    void performAction() override;
};

class GooseNesting : public NonOwnableProperty {
  public:
    void performAction() override;
};

class Tuition : public NonOwnableProperty {
  public:
    void performAction() override;
};

class CoopFee : public NonOwnableProperty {
  public:
    void performAction() override;
};

class SLC : public NonOwnableProperty {
  public:
    void performAction() override;
};

class NH : public NonOwnableProperty {
  public:
    void performAction() override;
};

#endif