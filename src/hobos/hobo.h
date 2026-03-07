#ifndef HOBO_H
#define HOBO_H

#include <string>
#include <memory>
#include <vector>

#include "actions.h"
#include "stash/zoo.h"
// #include "stash/items.h"
// #include "stash/inventory.h"
#include "creatures/creature.h"


struct CreatureInfo;
struct BattleContext;
class BattleMenu;

struct ChoiceContext {
    int lastMoveChoice = -1;
    int lastItemChoice = -1;
    int lastItemTarget = -1;
    int lastSwapTarget = -1;
};

class Hobo {
protected:
    const std::string name;
    std::unique_ptr<Zoo> zoo;
    int numCreatures;
    // std::unique_ptr<Inventory> inventory;
    int numItems;
    // std::unique_ptr<Item> booze;
    int alchoholMeter;

    ChoiceContext _choiceCtx;
    Action _lastAction;

public:
    Hobo(const std::string hoboName, std::string zooName);
    Zoo& getZoo() const;
    Creature* getCreature(int creatureKey) const;
    Creature* getStarter() const; 
    // Inventory& getItems() const;
    std::string getName() const;
    int getNumCreatures() const;
    int getNumItems() const;
    // void addItem(Item *item);
    void addCreature(Creature *creature);
    // void selectItem(int itemKey);
    // void selectCreature();
    // void useItem(Item *item);   
    void drinkAlchohol();

    void resetChoiceContext();
    const ChoiceContext& getChoiceContext() const;
    const Action& getLastAction() const;
    virtual Action nextAction(Creature *active,const BattleContext &ctx, 
        BattleMenu &menu) = 0;

    CreatureInfo makeCreatureInfo(Creature *creature, bool isActive = false);
    std::vector<CreatureInfo> makeZooInfo();
    virtual ~Hobo();
};

#endif
