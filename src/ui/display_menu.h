#ifndef DISPLAY_MENU_H
#define DISPLAY_MENU_H

#include <string>
#include <vector>

#include "creatures/status.h"

class Battle;

template <typename T>
using Info = std::vector<T>; 
using str  = std::string;

struct MoveInfo {
    str    name;
    int    power;
    int    accuracy;
    int    effectChance;
    Status effect;
};

struct CreatureInfo {
    str            name;
    int            hp;
    int            maxHp;
    int            attack;
    int            defense;
    int            speed;
    Status         status;
    str            statusName;
    bool           alive;
    bool           isActive;
    Info<MoveInfo> moves;
    int            moveCount;
};

struct ItemInfo {
    str name;
    int quantity;
};

struct BoozeInfo {
    int sipsLeft;
    int attackBoost;
    int defenseBoost;
    int fleeChanceIncrease;
};

struct BattleContext {
    str                playerName;
    str                enemyName;
    CreatureInfo       playerActive;
    CreatureInfo       enemyActive;
    Info<CreatureInfo> zoo;
    Info<ItemInfo>     items;
    BoozeInfo          booze;           
};


class DisplayMenu {
private:
    BattleContext _context;
    int _lastMoveChoice = -1;
    int _lastItemChoice = -1;
    int _lastItemTarget = -1;
    int _lastSwapTarget = -1;

    static constexpr int WIDTH = 62;

    // Sub-menus (returns 0 = back)
    int _showMoveMenu();
    int _showItemMenu();
    int _showBoozeMenu();
    int _showSwapMenu();
    void _showInfoMenu();

    // UI helpers
    void _printBattleHeader() const;
    void _printCreatureCard(const CreatureInfo &creature) const;

public:
    DisplayMenu(const BattleContext &context);

    // Entry points called by PlayerHobo

    // Pre-battle menu: returns 1 = Fight, 2 = Run
    int showPreBattle();
    
    // Battle menu returns one of the options values below
    // Sub-menus are handled internally
    //
    // 1  = UseMove   (call getMoveChoice() afterwards)
    // 2  = UseItem   (call getItemChoice() / getItemTarget() afterwards)
    // 3  = DrinkBooze
    // 4  = SwapCreature (call getSwapTarget() afterwards)
    // 5  = Info
    // 0  = (internal back, should not surface to caller)
    int showBattleMenu(); 

    // Secondary getters (called after showBattleMenu returns) 
    int getMoveChoice() const { return _lastMoveChoice; }
    int getItemChoice() const { return _lastItemChoice; }
    int getItemTarget() const { return _lastItemTarget; }
    int getSwapTarget() const { return _lastSwapTarget; }


    friend class Battle;
};

#endif 