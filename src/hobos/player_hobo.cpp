#include "player_hobo.h"
#include "actions.h"
#include "battle.h"
#include "items/item.h"
#include "ui/battle_menu.h"
#include "creatures/creature.h"
#include <iostream>


PlayerHobo::PlayerHobo(const std::string hoboName, std::string zooName) 
: Hobo(hoboName, zooName) {}

Action PlayerHobo::nextAction(Creature *active, 
    const BattleContext &context, BattleMenu &menu) {

    if (active == nullptr) {
        while (true) {
            int rosterIdx = menu.promptSwapMenu(context);
            if (rosterIdx == 0) {
                std::cout << "\nYou must send out a creature!\n";
                continue;
            }
            
            _choiceCtx.lastSwapTarget = rosterIdx;
            Creature *incomming = zoo->getStashItem(this, rosterIdx);

            if (!incomming->isAlive()) {
                std::cout << "That creatuse has already fainted!";
                continue;
            }

            _lastAction = SwapCreature{ nullptr, incomming};
            return _lastAction;
        }
    }

    while (true) {
        int topChoice = menu.showBattleMenu(context);
        _choiceCtx = ChoiceContext{};

        switch (topChoice) {

            case 1: {
                int moveIdx = menu.promptMoveMenu(context);
                if (moveIdx == 0) continue;   // back

                Move *move = active->getMove(moveIdx - 1);
                if (!move) continue;

                _choiceCtx.lastMoveChoice = moveIdx;
                _lastAction = UseMove{ move };
                return _lastAction;
            }

            case 2: {
                int itemIdx = menu.promptItemMenu(context);
                if (itemIdx == 0) continue;

                _choiceCtx.lastItemChoice = itemIdx;
                Item *item = inventory->getStashItem(this, itemIdx);
                
                int remaining = inventory->decrementNumItems(item);
                if (remaining == 0) {
                    inventory->remove(this, itemIdx);
                }
                
                int creatureIdx = menu.promptItemCreature(context);
                Creature *creature = zoo->getStashItem(this, creatureIdx);

                int confirm = menu.promptItemConfirm(context, creatureIdx, itemIdx);
                if (confirm == 0) continue;

                _lastAction = UseItem{ item, creature};
                return _lastAction;
            }

            case 3: {
                int confirm = menu.promptBoozeMenu(context);
                if (confirm == 0) continue;

                _lastAction = DrinkBooze{ booze.get() };
                return _lastAction;
            }

            case 4: {
                int rosterIdx = menu.promptSwapMenu(context);
                if (rosterIdx == 0) continue;

                int confirm = menu.promptSwapConfirm(context, rosterIdx);
                if (confirm == 0) continue;

                _choiceCtx.lastSwapTarget = rosterIdx;
                Creature *incoming = zoo->getStashItem(this, rosterIdx);
                _lastAction = SwapCreature{ active, incoming };
                return _lastAction;
            }

            case 5: {
                menu.showInfoMenu();
                continue;   // back to top-level menu
            }

            default:
                continue;
        }
    }
}
