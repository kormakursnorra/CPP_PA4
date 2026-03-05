#ifndef ENEMY_H
#define ENEMY_H

#include "hobos/hobo.h"
#include <sys/types.h>


enum PowerLvl {
    LOW = 0, MEDIUM = 1, HIGH = 2, TWEAKER = 3
};


class EnemyHobo : public Hobo {
private:
    int lastAction;
    int numInitActions; // 0 for selecting Creature, 1 for selecting Item 

    void fillZoo() const;
    void fillInventory() const;

public:
    PowerLvl powerLvl;
    EnemyHobo(const std::string enemyName, std::string zooName);
    int nextAction();
    int getLastAction();
};

#endif
