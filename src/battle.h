#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

#include "hobos/hobo.h"
#include "ui/battle_menu.h"
#include "creatures/creature.h"

template <typename T>
using Info = std::vector<T>; 
using str  = std::string;

struct MoveInfo {
    str name;
    int power;
    int accuracy;
    int effectChance;
    Status effect;
    int effectDuration;
};

struct CreatureInfo {
    str name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    Status status;
    str statusName;
    bool alive;
    bool isActive;
    Info<MoveInfo> moves;
    int moveCount = 0;
};

struct ItemInfo {
    str name;
    str description;
    ItemType type;
    int effect;
};

struct BoozeInfo {
    int sipsLeft;
    int attackBoost;
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


class Battle {
private:
    Hobo *player;
    Hobo *enemy;
    Creature *playerActive;
    Creature *enemyActive;
    BattleMenu menu;

    BattleContext buildContext() const;
    
    int calcDmg(Creature *attacker, Move *move) const;
    int calcBoozeEffect(Zoo *zoo, Item* booze) const;
    
    bool applyPlayerAction(const Action &action);
    bool applyEnemyAction(const Action &action);
    bool hasAliveCreatures(Hobo* hobo) const;

public:
    Battle(Hobo* player, Hobo* enemy);
    void run();
};

#endif
