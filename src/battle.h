#ifndef BATTLE_H
#define BATTLE_H

#include "creatures/creature.h"
#include "hobos/hobo.h"
#include "hobos/player_hobo.h"
#include "hobos/enemy_hobo.h"

class Battle {
private:
    PlayerHobo* player;
    EnemyHobo* opponent;

    Hobo* whoGoesFirst();
    Hobo* whoGoesSecond();
    int calcDmg(Creature* attacker, Move* move);
    void displayStatus();
    void doTurn(Creature* attacker, Creature* defender);

public:
    Battle(PlayerHobo* player, EnemyHobo* opponent);
    void run();
};

#endif
