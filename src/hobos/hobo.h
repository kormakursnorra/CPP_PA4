#ifndef HOBO_H
#define HOBO_H

#include "creatures/creature.h"
#include "stash/inventory.h"
#include "hobos/actions.h"
// #include "stash/items.h"
#include "stash/zoo.h"

#include <string>
#include <memory>



class Hobo {
protected:
    const std::string name;
    std::unique_ptr<Zoo> zoo;
    int numCreatures;
    // std::unique_ptr<Inventory> inventory;
    // std::unique_ptr<Item> booze;
    int numItems;
    
    int alchohol_meter;
    
public:

    Hobo(const std::string hoboName, std::string zooName);
    Zoo& getZoo() const;
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
    virtual Action nextAction(Creature *active);
    virtual ~Hobo();

    friend class Battle;
};

#endif
