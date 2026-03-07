#include "hobos/player_hobo.h"
#include "creatures/creature.h"
#include "ui/display_menu.h"
#include "hobos/hobo.h"

#include <cstdlib>
#include <iostream>

PlayerHobo::PlayerHobo(const std::string hoboName, std::string zooName) 
: Hobo(hoboName, zooName) {}

static CreatureInfo makeCreatureInfo(Creature *creature, bool isActive) {
    CreatureInfo info;
    info.name       = creature->getName();
    info.hp         = 0;
    info.maxHp      = 1;
    info.attack     = creature->getAttack();
    info.defense    = creature->getDefense();
    info.speed      = creature->getSpeed();
    info.status     = creature->getStatus();
    info.statusName = creature->getStatusName();
    info.alive      = creature->isAlive();
    info.isActive   = isActive;

    for (int i = 1; i <= 4; ++i) {
        Move* move = creature->getMove(i);
        if (!move) { continue; }
        MoveInfo moveInfo;
        moveInfo.name         = move->getName();
        moveInfo.power        = move->getPower();
        moveInfo.effect       = move->getEffect();
        moveInfo.accuracy     = move->getAccuracy();
        moveInfo.effectChance = move->getEffectChance();
        info.moves.push_back(moveInfo);
    }

    return info;
}

Action PlayerHobo::nextAction(Creature *active) {
    MenuContext context;
    bool isActive       = false;
    context.playerName  = name;
    context.enemyName   = "???";
    context.active      = makeCreatureInfo(active, isActive);

    auto *stashContents = zoo->getStash(this);
    for (auto& [key, creature] : *stashContents) {
        if (creature == active) {
            isActive = true;
        }
        context.zoo.push_back(makeCreatureInfo(creature, isActive)); 
    }
    
    // context.booze = {
    //     ,
    // }

    DisplayMenu menu(context);
    int topChoice = menu.showBattleMenu();

    switch (topChoice) {
        case 1: {
            Move* move = active->getMove(menu.getMoveChoice());
            return UseMove{ move };
        }
        case 2: {
            // return UseItem{ ... };
        }
        case 3: {
            return DrinkBooze{};
        }
        case 4: {
            int rosterIdx = menu.getSwapTarget();
            Creature* incoming = zoo->getStashItem(this, rosterIdx);
            return SwapCreature{ active, incoming };
        }
        default:
            return DrinkBooze{};
    }
}
