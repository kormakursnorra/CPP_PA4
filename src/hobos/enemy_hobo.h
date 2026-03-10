#ifndef ENEMY_H
#define ENEMY_H

#include <sys/types.h>

#include "hobo.h"
#include "actions.h"
#include "creatures/creature.h"


enum PowerLvl {
    LOW     = 0, 
    MEDIUM  = 1, 
    HIGH    = 2, 
    TWEAKER = 3
};

class BattleMenu;
struct BattleContext;

class EnemyHobo : public Hobo {
private:
    void fillZoo() const;
    void fillInventory() const;

public:
    PowerLvl powerLvl;
    EnemyHobo(const std::string enemyName, std::string zooName);
    Action nextAction(Creature *active,
        const BattleContext &ctx, BattleMenu &menu) override;
};

#endif
