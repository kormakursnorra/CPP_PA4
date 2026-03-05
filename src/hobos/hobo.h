#ifndef HOBO_H
#define HOBO_H

#include "zoos/zoo.h"
// #include "items.h"

#include <string>
#include <memory>


// typedef std::unique_ptr<Inventory> upInventory;
typedef std::unique_ptr<Zoo> upZoo;

class Hobo {
protected:
    const std::string name;
    
    upZoo zoo;
    int numCreatures;
    // Inventory *items;
    // std::unique_ptr<Item> booze;
    int numItems;
    
    
public:
    int alchohol_meter;
    Hobo(const std::string hoboName, std::string zooName);
    upZoo& getZoo();
    // Item* getItems() const;
    // void addItem(Item *item);
    // void useItem(Item *item);   
    void addCreature();
    void drinkAlchohol();
    virtual int nextAction();
    virtual ~Hobo();
};

#endif
