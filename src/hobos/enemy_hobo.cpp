#include <cstdlib>
#include <cassert>

#include "actions.h"
#include "enemy_hobo.h"
#include "battle.h"
#include "items/item.h"
#include "ui/battle_menu.h"
#include "creatures/creature.h"


EnemyHobo::EnemyHobo(const std::string enemyName, std::string zooName) 
: Hobo(enemyName, zooName) {}

Action EnemyHobo::nextAction(Creature *active, const BattleContext &, BattleMenu &) {
    int actionChoice = rand() % 100;
    int itemCount = inventory->getNumContents(this);

    if (actionChoice <= 75 || itemCount == 0) {
        int moveCount = 0;
        int candidates[4];
        for (int i = 0; i < 4; ++i) {
            Move *move = active->getMove(i);
            if (move && move->getPower() > 0) {
                candidates[moveCount++] = i;
            }
        }

        if (moveCount == 0) {
            for (int i = 0; i < 4; ++i) {
                Move *move = active->getMove(i);
                if (move) {
                    candidates[moveCount++] = i;
                }
            }
        }

        if (moveCount == 0) {
            _lastAction = SwapCreature{ active, active };
            return _lastAction;
        }
    
        int chosen = candidates[rand() % moveCount];
        Move *move = active->getMove(chosen);
    
        _choiceCtx.lastMoveChoice = chosen + 1;   // store 1-based
        _lastAction = UseMove{ move };
    }
    else {
        int choice;
        Item *itemChosen = nullptr;
        int attempts = 0;
        while (!itemChosen && attempts < (itemCount * 2)) {
            choice = (rand() % itemCount) + 1;
            Item *item = inventory->getStashItem(this, choice);
            if (item) {
                itemChosen = item;
            }
            attempts++;
        }

        if (!itemChosen) {
            int moveCount = 0;
            int candidates[4];
            for (int i = 0; i < 4; ++i) {
                Move *move = active->getMove(i);
                if (move) {
                    candidates[moveCount++] = i;
                }
            }

            if (moveCount == 0) {
                _lastAction = SwapCreature{ active, active };
                return _lastAction;
            }

            int chosen = candidates[rand() % moveCount];
            Move *move = active->getMove(chosen);
            _choiceCtx.lastMoveChoice = chosen + 1;
            _lastAction = UseMove{ move };
            return _lastAction;
        }
        
        _choiceCtx.lastItemChoice = choice;
        _lastAction = UseItem { itemChosen, active}; 
    }
    
    return _lastAction;
}