#ifndef FRIENDLY_CREATURE_H
#define FRIENDLY_CREATURE_H

#include "creatures/creature.h"

class FriendlyCreature : public Creature {
public: 
    FriendlyCreature(std::string name, int hp, int attack, int defense, int speed);
    Move* nextAction();
};

#endif