#ifndef ENEMY_H
#define ENEMY_H

#include <sys/types.h>

#include "hobo.h"
#include "actions.h"
#include "creatures/creature.h"

class BattleMenu;
struct BattleContext;

class EnemyHobo : public Hobo {
public:
    EnemyHobo(const std::string enemyName, std::string zooName);
    Action nextAction(Creature *active,
        const BattleContext &ctx, BattleMenu &menu) override;
};

#endif
