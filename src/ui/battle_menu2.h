#ifndef BATTLE_MENU2_H
#define BATTLE_MENU2_H
#include <string>

struct BattleContext;
struct CreatureInfo;

class BattleMenu {
    private:
        void _printBattleHeader(const BattleContext& context) const;
        void _printCreatureCard(const CreatureInfo &creature)  const;
    
    public:
        BattleMenu() = default;
        int showBattleMenu(const BattleContext& context);
        int promptMoveMenu(const BattleContext& context) const;
        int promptItemMenu(const BattleContext& context) const;
        int promptItemCreature(const BattleContext& contex) const;
        int promptItemConfirm(const BattleContext& contex, int creatureIndex, int itemIndex) const;
        int promptBoozeMenu(const BattleContext& context) const;
        int promptSwapMenu(const BattleContext& context) const;
        int promptSwapConfirm(const BattleContext& context, int rosterIndex) const;
        void showInfoMenu() const;
        void showTurnResult(const std::string& message) const;
        void showBattleOver(const std::string& winnerName) const;

};
#endif