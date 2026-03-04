#ifndef BATTLE_H
#define BATTLE_H

#include "entity.h"

class Battle {
private:
    Entity* player;
    Entity* opponent;

    Entity* whoGoesFirst();
    Entity* whoGoesSecond();
    int calcDmg(Entity* attacker, Move* move);
    void displayStatus();
    void doTurn(Entity* attacker, Entity* defender);

public:
    Battle(Entity* player, Entity* opponent);
    void run();
};

#endif
