#ifndef BOOZE_H
#define BOOZE_H

#include "creatures/creature.h"
#include "item.h"

class Booze : public Item<Booze> {
public: 
    Booze(const std::string name, const std::string description, int effect);
    bool applyItem(Creature *target);
};  

#endif