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
    Booze *booze = player->getBooze();
    context.playerName   = player->getName();
    context.enemyName    = enemy->getName();
    context.playerActive = player->makeCreatureInfo(playerActive, true);
    context.enemyActive  = enemy->makeCreatureInfo(enemyActive,  true);
    context.zoo          = player->makeZooInfo();
    context.items        = player->makeInventoryInfo();
    context.booze        = player->makeBoozeInfo(booze);
    return context;
}


int Battle::calcDmg(Creature *attacker, Move *move) const {
    if (!move->hits()) { 
        return 0;
    }

    int baseDmg = (attacker->getAttack() * move->getPower()) / 100;

    if (attacker->getStatus() == WEAKENED) {
        baseDmg = baseDmg / 2;
    }

    if (attacker->getStatus() == SCARED) {
        if (rand() % 100 < 30) {
            std::cout << " " << attacker->getName() << " is to scared to attack!\n";
            return 0;
        }
    }

    bool crit = (rand() % 100) < 10;
    if (crit) {
        std::cout << tui::FG_YELLOW << "  Critical hit!" << tui::RESET << "\n";
        baseDmg *= 2;
    }
    return baseDmg;
}

bool Battle::applyPlayerAction(const Action &action) {
    return std::visit([&](auto &&act) -> bool {
        using T = std::decay_t<decltype(act)>;

        if constexpr (std::is_same_v<T, UseMove>) {
            int fleeChance = player->getAlcoholMeter() * 15;
            if (fleeChance > 0 && (rand() % 100) < fleeChance) {
                std::ostringstream msg;
                msg << " " << playerActive->getName()
                    << " fled in fear and refuses to fight!";
                menu.showTurnResult(msg.str());
                return true;
            }
            int dmg = calcDmg(playerActive, act.move);
            enemyActive->takeDamage(dmg);

            std::ostringstream msg;
            msg << "  " << playerActive->getName()
                << " uses " << act.move->getName()
                << " dealing " << dmg << " damage!";
            menu.showTurnResult(msg.str());

            if (act.move->getEffect() != NONE) {
                int chance = rand() % 100;
                if (chance < act.move->getEffectChance()) {
                    enemyActive->setStatus(act.move->getEffect(), act.move->getEffectDuration());
                }
            }

            return true;
        }
        else if constexpr (std::is_same_v<T, UseItem>) {
            bool applied = act.item->applyItem(playerActive);
            if (!applied) return false;
            std::ostringstream msg;
            msg << "  " << player->getName()
                << " used " << act.item->getItemName()
                << " !";
            return true;
        }
        else if constexpr (std::is_same_v<T, DrinkBooze>) {
            player->drinkBooze();
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

            if (act.move->getEffect() != NONE) {
                int chance = rand() % 100;
                if (chance < act.move->getEffectChance()) {
                    playerActive->setStatus(act.move->getEffect(), act.move->getEffectDuration());
                }
            }

            return true;
        }
        else if constexpr (std::is_same_v<T, UseItem>) {
            bool applied = act.item->applyItem(enemyActive);
            if (!applied) return false;
            std::ostringstream msg;
            msg << "  " << enemy->getName()
                << " used " << act.item->getItemName()
                << " !";
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

bool Battle::hasAliveCreatures(Hobo* hobo) const {
    const auto* zoo = hobo->getZoo().getStash(hobo);
    for (const auto& [key, creature]: *zoo) {
        if (creature->isAlive()) {
            return true;
        }
    }
    return false;
}

void Battle::run() { 
    // while (playerActive->isAlive() && enemyActive->isAlive())
    while(true) {

        bool playerStunned = (playerActive->getStatus() == STUNNED);
        bool enemyStunned = (enemyActive->getStatus() == STUNNED);

        std::string pmsg = playerActive->applyStatusEffect();
        if (!pmsg.empty()) {
            menu.showTurnResult(" " + pmsg);
        }
        if (!playerActive->isAlive()) {
            if (hasAliveCreatures(player)) {
                BattleContext ctx = buildContext();
                Action swapAction = player->nextAction(nullptr, ctx, menu);
                applyPlayerAction(swapAction);
            } else {
                break;
            }
        }
        std::string emsg = enemyActive->applyStatusEffect();
        if (!emsg.empty()) {
            menu.showTurnResult(" " + emsg);
        }
        if (!enemyActive->isAlive()) {
            std::ostringstream deathMsg;
            deathMsg << " " << enemyActive->getName() << " has been defeated!";
            menu.showTurnResult(deathMsg.str());
            if (hasAliveCreatures(enemy)) {
                const auto* stash = enemy->getZoo().getStash(enemy);
                for (const auto& [key, creature] : *stash) {
                    if (creature->isAlive()) {
                        std::ostringstream msg;
                        msg << "  " << enemy->getName() << " sends out " << creature->getName() << "!";
                        menu.showTurnResult(msg.str());
                        enemyActive = creature;
                        break;
                    }
                }
            } else {
                break;
            }
        }

        player->resetChoiceContext();
        enemy->resetChoiceContext();

        BattleContext ctx = buildContext();

        bool playerFirst = playerActive->getSpeed() >= enemyActive->getSpeed();
        Action playerAction, enemyAction;
        if (!playerStunned) {
            playerAction = player->nextAction(playerActive, ctx, menu);
        }
        if (!enemyStunned) {
            enemyAction = enemy->nextAction(enemyActive, ctx, menu);
        }

        if (playerFirst) {
            if (!playerStunned) {
                applyPlayerAction(playerAction);
                if (!enemyActive->isAlive()) {
                    continue;
                }
            }
            if (!enemyStunned) {
                applyEnemyAction(enemyAction);
            }
        } else {
            if (!enemyStunned) {
                applyEnemyAction(enemyAction);
                if (!playerActive->isAlive()) {
                    continue;
                }
            }
            if (!playerStunned) {
                applyPlayerAction(playerAction);
            }
        }

        player->lessDrunk();
    }

    std::string winner = playerActive->isAlive()
        ? player->getName()
        : enemy->getName();
    menu.showBattleOver(winner);
}