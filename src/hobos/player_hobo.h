#ifndef PLAYER_H
#define PLAYER_H

#include "hobos/actions.h"
#include "hobos/hobo.h"

class PlayerHobo : public Hobo {
public:
    PlayerHobo(const std::string hoboName, std::string zooName);
    Action nextAction(Creature *active) override;
};

#endif
