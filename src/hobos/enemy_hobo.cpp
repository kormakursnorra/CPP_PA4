#include "hobos/enemy_hobo.h"
#include "creatures/creature.h"
#include "hobos/actions.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

EnemyHobo::EnemyHobo(const std::string enemyName, std::string zooName) 
: Hobo(enemyName, zooName) {
    int randLevel = rand() % 4;
    powerLvl = static_cast<PowerLvl>(randLevel);
    fillZoo();
    fillInventory();
    

    numCreatures = zoo->getNumContents(this);
    // numItems = inventory->getNumContents(this) + 1;
}

void EnemyHobo::fillZoo() const {
    return;
}

Action EnemyHobo::nextAction(Creature *active) {
       
}
