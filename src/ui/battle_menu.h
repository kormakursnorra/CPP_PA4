#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

#include <string>

struct BattleContext;
struct CreatureInfo;

class BattleMenu {
private:
    static constexpr int WIDTH = 62;
    
    // UI helpers
    void _printBattleHeader(const BattleContext &ctx) const;
    void _printCreatureCard(const CreatureInfo &creature)  const;
    
public:
    BattleMenu() = default;    

    // Main Battle Menu
    int showBattleMenu(const BattleContext &context); 
   
    int promptMoveMenu(const BattleContext &ctx) const;
    int promptItemMenu(const BattleContext &ctx) const;
    // int promptCreatureSelect(const BattleContext &ctx) const;
    int promptItemConfirm(const BattleContext &ctx, int itemIdx) const;
    int promptBoozeMenu(const BattleContext &ctx) const;
    int promptSwapMenu(const BattleContext &ctx) const;
    int promptSwapConfirm(const BattleContext &ctx, int rosterIdx) const;
    void showInfoMenu() const;
    
    void showTurnResult(const std::string &message)    const;
    void showBattleOver(const std::string &winnerName) const;
};

#endif 