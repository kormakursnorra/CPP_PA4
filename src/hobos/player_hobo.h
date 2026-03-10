#ifndef PLAYER_H
#define PLAYER_H

#include "hobo.h"
#include "actions.h"

class PlayerHobo : public Hobo {
public:
    PlayerHobo(const std::string hoboName, std::string zooName);
    Action nextAction(Creature *active, 
        const BattleContext &ctx, BattleMenu &menu) override;
};

#endif
