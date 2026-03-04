#ifndef ENEMY_CREATURE_H
#define ENEMY_CREATURE_H

#include "creatures/creature.h"

class EnemyCreature : public Creature {
public: 
    EnemyCreature(std::string name, int hp, int attack, int defense, int speed);
    Move* nextAction();
};

#endif