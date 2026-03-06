#ifndef ACTIONS_H
#define ACTIONS_H

#include "creatures/creature.h"
#include "creatures/move.h"
#include <variant>


struct UseMove { Move *move; };

struct UseItem {
    // Item *item;
};

struct DrinkBooze { 
    // Item *drink; 
};

struct SwapCreature { 
    Creature *active; 
    Creature *incoming;
};



using Action = std::variant<UseMove, UseItem, DrinkBooze, SwapCreature>;

#endif