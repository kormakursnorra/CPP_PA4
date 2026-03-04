#ifndef BOSS_H
#define BOSS_H

#include "enemy.h"

class Boss : public Enemy {
private:
    bool enraged; // tracks if boss is mad

    Move* strongestMove(); // finds highest power move

public:
    Boss(std::string name, int hp, int attack, int defense, int speed);
    Move* chooseAction();
};

#endif
