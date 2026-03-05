#ifndef ENEMY_CREATURE_H
#define ENEMY_CREATURE_H

#include "creatures/creature.h"
#include <cstdint>

class EnemyCreature : public Creature {
public: 
    EnemyCreature(std::string name, uint8_t hp, 
        uint8_t attack, uint8_t defense, uint8_t speed
    );
};

#endif