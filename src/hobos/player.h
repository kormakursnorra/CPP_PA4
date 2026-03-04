#ifndef PLAYER_H
#define PLAYER_H

#include "hobos/hobo.h"

class Player : public Hobo {
public:
    Player(std::string name);
    Move* chooseAction();
};

#endif
