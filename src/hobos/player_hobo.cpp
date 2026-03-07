#include "player_hobo.h"
#include "actions.h"
#include "battle.h"
#include "ui/battle_menu.h"
#include "creatures/creature.h"


PlayerHobo::PlayerHobo(const std::string hoboName, std::string zooName) 
: Hobo(hoboName, zooName) {}

Action PlayerHobo::nextAction(Creature *active, 
    const BattleContext &context, BattleMenu &menu) {

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
                // TODO: for inventory
                _lastAction = UseItem{};
                return _lastAction;
            }

            case 3: {
                int confirm = menu.promptBoozeMenu(context);
                if (confirm == 0) continue;

                _lastAction = DrinkBooze{};
                return _lastAction;
            }

            case 4: {
                int rosterIdx = menu.promptSwapMenu(context);
                if (rosterIdx == 0) continue;

                int confirm = menu.promptSwapConfirm(context, rosterIdx);
                if (confirm == 0) continue;

                _choiceCtx.lastSwapTarget = rosterIdx;
                Creature *incoming = zoo->getStashItem(this, rosterIdx - 1);
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
