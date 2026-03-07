#ifndef ENEMY_H
#define ENEMY_H

#include "creatures/creature.h"
#include "hobos/actions.h"
#include "hobos/hobo.h"
#include <sys/types.h>


enum PowerLvl {
    LOW     = 0, 
    MEDIUM  = 1, 
    HIGH    = 2, 
    TWEAKER = 3
};

class EnemyHobo : public Hobo {
private:

    Action lastAction;

    void fillZoo() const;
    void fillInventory() const;

public:
    PowerLvl powerLvl;
    EnemyHobo(const std::string enemyName, std::string zooName);
    Action nextAction(Creature *active) override;
    Action getLastAction();
};

#endif
