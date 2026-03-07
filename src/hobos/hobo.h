#ifndef HOBO_H
#define HOBO_H

#include "creatures/creature.h"
#include "stash/inventory.h"
#include "hobos/actions.h"
// #include "stash/items.h"
#include "stash/zoo.h"
#include "ui/display_menu.h"

#include <string>
#include <memory>



class Hobo {
protected:
    const std::string name;
    std::unique_ptr<Zoo> zoo;
    int numCreatures;
    // std::unique_ptr<Inventory> inventory;
    int numItems;
    // std::unique_ptr<Item> booze;
    int alchoholMeter;
    
    
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
    virtual Action nextAction(Creature *active);
    virtual ~Hobo();
};

#endif
