#include "boss.h"
#include "creatures/move.h"
#include "battle.h"
#include <iostream>

Boss::Boss(const std::string name, std::string zooName)
    : EnemyHobo(name, zooName), enraged(false) {}

Move* Boss::strongestMove(Creature *active) {
    Move* stronges = nullptr;
    int maxPower = 0;
    for (int i = 0; i < 4; i++) {
        Move * move = active->getMove(i);
        if (move && move->getPower() > maxPower) {
            maxPower = move->getPower();
            stronges = move;
        }
    }
    return stronges;
}

Action Boss::nextAction(Creature *active, const BattleContext &ctx, BattleMenu &menu) {
    // check if boss is mad
    int aliveCount = 0;
    for (const auto& creature : ctx.zoo) {
        if (creature.alive) {
            aliveCount++;
        }
    }

    if (!enraged && aliveCount == 1) {
        enraged = true;
        std::cout << "\n*** " << getName()
            << " is down to their last creature! They are furious! ***\n";
    }

    if (enraged) {
        std::cout << getName() << " uses their strongest move!\n";
        Move* move = strongestMove(active);

        for (int i = 0; i < 4; i++) {
            if (active->getMove(i) == move) {
                _choiceCtx.lastMoveChoice = i + 1;
                break;
            }
        }

        _lastAction = UseMove{move};
        return _lastAction;
    }

    return EnemyHobo::nextAction(active, ctx, menu);
}