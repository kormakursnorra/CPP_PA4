#ifndef BOSS_H
#define BOSS_H

#include "hobos/enemy_hobo.h"

class Boss : public EnemyHobo {
private:
    bool enraged; // tracks if boss is mad

    Move* strongestMove(); // finds highest power move

public:
    Boss(const std::string name, std::string zooName);
    Move* nextAction();
};

#endif
