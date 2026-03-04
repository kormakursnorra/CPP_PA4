#ifndef ENEMY_H
#define ENEMY_H

#include "hobos/hobo.h"

#include <string>

class EnemyHobo : public Hobo {
public:
    EnemyHobo(const std::string name);
    Move* chooseAction();
};

#endif
