#ifndef FRIENDLY_CREATURE_H
#define FRIENDLY_CREATURE_H

#include "creatures/creature.h"
#include <cstdint>

class FriendlyCreature : public Creature {
public: 
    FriendlyCreature(std::string name, uint8_t hp, 
        uint8_t attack, uint8_t defense, uint8_t speed
    );
    Move* nextAction();
};

#endif