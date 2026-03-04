#ifndef CHARACTER_H
#define CHARACTER_H

#include "entity.h"

class Character : public Entity {
public:
    Character(std::string name, int hp, int attack, int defense, int speed);

    Move* chooseAction();
};

#endif
