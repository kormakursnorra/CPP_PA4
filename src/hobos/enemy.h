#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(std::string name, int hp, int attack, int defense, int speed);

    Move* chooseAction();
};

#endif
