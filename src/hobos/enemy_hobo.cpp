#include <cstdlib>
#include <cassert>

#include "actions.h"
#include "enemy_hobo.h"
#include "battle.h"
#include "ui/battle_menu.h"
#include "creatures/creature.h"


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

void EnemyHobo::fillInventory() const {
    return;
}

Action EnemyHobo::nextAction(Creature *active, const BattleContext &, BattleMenu &) {
    int moveCount = 0;
    int candidates[4];
    for (int i = 0; i < 4; ++i) {
        Move *move = active->getMove(i);
        if (move && move->getPower() > 0) {
            candidates[moveCount++] = i;
        }
    }

    if (moveCount == 0) {
        _lastAction = DrinkBooze{};
        return _lastAction;
    }

    int chosen    = candidates[rand() % moveCount];
    Move *move    = active->getMove(chosen);

    _choiceCtx.lastMoveChoice = chosen + 1;   // store 1-based
    _lastAction = UseMove{ move };
    return _lastAction;
}