#include "hobos/enemy_hobo.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

EnemyHobo::EnemyHobo(const std::string enemyName, std::string zooName) 
: Hobo(enemyName, zooName) {
    int randLevel = rand() % 4;
    powerLvl = static_cast<PowerLvl>(randLevel);
    fillZoo();
    fillInventory();
    
    lastAction = -1;
    numInitActions = 1;
    numItems = zoo->getNumMembers(this) + 1;
    numCreatures = zoo->getNumMembers(this);
}

void EnemyHobo::fillZoo() const {
    return;
}

int EnemyHobo::nextAction() {
    int action = 0;
    if (lastAction == -1) {
        action = rand() % numInitActions;
    }
    assert(0 == action || action == 1);
    lastAction = action;
    return action;
}
