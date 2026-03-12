#include <iostream>
#include <sstream>
#include <cstdlib>
#include <type_traits>
#include <variant>

#include "items/item.h"
#include "ui/tui.h"
#include "battle.h"
#include "hobos/actions.h"
#include "ui/battle_menu.h"
#include "hobos/enemy_hobo.h"
#include "hobos/player_hobo.h"
#include "creatures/creature.h"

Battle::Battle(Hobo *player, Hobo *enemy)
: player(player), enemy(enemy), menu() {
    playerActive = player->getStarter();
    enemyActive  = enemy->getStarter();
}

BattleContext Battle::buildContext() const {
    BattleContext context;
    context.playerName   = player->getName();
    context.enemyName    = enemy->getName();
    context.playerActive = player->makeCreatureInfo(playerActive, true);
    context.enemyActive  = enemy->makeCreatureInfo(enemyActive,  true);
    context.zoo          = player->makeZooInfo();
    context.items        = player->makeInventoryInfo();
    context.booze        = player->makeBoozeInfo();
    return context;
}


int Battle::calcDmg(Creature *attacker, Move *move) const {
    if (!move->hits()) { return 0; }
    int dmg = (attacker->getAttack() * move->getPower()) / 100;
    bool crit = (rand() % 100) < 10;
    if (crit) {
        std::cout << tui::FG_YELLOW << "  Critical hit!" << tui::RESET << "\n";
        dmg *= 2;
    }
    return dmg;
}

int calcEffect(Creature *receiver, Item *item) const {
    ItemType type = item->getItemType();     
    if constexpr (std::is_same_v<type, HEAL>) {

    } 
    int effect = item->getItemEffect() / 100;
}


bool Battle::applyPlayerAction(const Action &action) {
    return std::visit([&](auto &&act) -> bool {
        using T = std::decay_t<decltype(act)>;

        if constexpr (std::is_same_v<T, UseMove>) {
            int dmg = calcDmg(playerActive, act.move);
            enemyActive->takeDamage(dmg);

            std::ostringstream msg;
            msg << "  " << playerActive->getName()
                << " uses " << act.move->getName()
                << " dealing " << dmg << " damage!";
            menu.showTurnResult(msg.str());
            return true;
        }
        else if constexpr (std::is_same_v<T, UseItem>) {
            int effect = calcEffect(act.receiver, act.item);
            playerActive->

            menu.showTurnResult("  " + player->getName() + " used an item.");
            return true;
        }
        else if constexpr (std::is_same_v<T, DrinkBooze>) {
            // TODO: apply booze effect
            menu.showTurnResult("  " + player->getName() + " takes a swig!");
            return true;
        }
        else if constexpr (std::is_same_v<T, SwapCreature>) {
            playerActive = act.incoming;
            std::ostringstream msg;
            msg << "  " << player->getName()
                << " swaps to " << act.incoming->getName() << "!";
            menu.showTurnResult(msg.str());
            return true;
        }
        else {   // NoAction
            return true;
        }
    }, action);
}

bool Battle::applyEnemyAction(const Action &action) {
    return std::visit([&](auto &&act) -> bool {
        using T = std::decay_t<decltype(act)>;

        if constexpr (std::is_same_v<T, UseMove>) {
            int dmg = calcDmg(enemyActive, act.move);
            playerActive->takeDamage(dmg);

            std::ostringstream msg;
            msg << "  " << enemyActive->getName()
                << " uses " << act.move->getName()
                << " dealing " << dmg << " damage!";
            menu.showTurnResult(msg.str());
            return true;
        }
        else if constexpr (std::is_same_v<T, UseItem>) {
            menu.showTurnResult("  " + enemy->getName() + " rummages through their coat...");
            return true;
        }
        else if constexpr (std::is_same_v<T, DrinkBooze>) {
            menu.showTurnResult("  " + enemy->getName() + " chugs from a paper bag!");
            return true;
        }
        else if constexpr (std::is_same_v<T, SwapCreature>) {
            enemyActive = act.incoming;
            std::ostringstream msg;
            msg << "  " << enemy->getName()
                << " sends out " << act.incoming->getName() << "!";
            menu.showTurnResult(msg.str());
            return true;
        }
        else {
            return true;
        }
    }, action);
}

void Battle::run() { 
    while (playerActive->isAlive() && enemyActive->isAlive()) {

        player->resetChoiceContext();
        enemy->resetChoiceContext();

        BattleContext ctx = buildContext();

        Action playerAction = player->nextAction(playerActive, ctx, menu);

        Action enemyAction = enemy->nextAction(enemyActive, ctx, menu);

        applyPlayerAction(playerAction);
        if (!enemyActive->isAlive()) { break; }

        applyEnemyAction(enemyAction);
        if (!playerActive->isAlive()) { break; }
    }

    std::string winner = playerActive->isAlive()
        ? player->getName()
        : enemy->getName();
    menu.showBattleOver(winner);
}