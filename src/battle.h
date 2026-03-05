#ifndef BATTLE_H
#define BATTLE_H

#include "hobos/hobo.h"

class Battle {
private:
    Hobo* player;
    Hobo* opponent;

    Hobo* whoGoesFirst();
    Hobo* whoGoesSecond();
    int calcDmg(Creature* attacker, Move* move);
    void displayStatus();
    void doTurn(Creature* attacker, Creature* defender);

public:
    Battle(Hobo* player, Hobo* opponent);
    void run();
};

#endif
