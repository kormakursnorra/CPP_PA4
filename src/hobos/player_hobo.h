#ifndef PLAYER_H
#define PLAYER_H

#include "hobos/hobo.h"

class PlayerHobo : public Hobo {
public:
    PlayerHobo(const std::string hoboName, std::string zooName);
    int nextAction();
};

#endif
