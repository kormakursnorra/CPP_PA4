#ifndef HOBO_H
#define HOBO_H

#include "zoos/zoo.h"
// #include "items.h"

#include <string>
#include <memory>
#include <vector>


// typedef std::vector<unique_ptr<Item>> Items;

class Hobo {
private:
    const std::string name;
    std::unique_ptr<Zoo> zoo;
    // std::unique_ptr<Item> *items;
    // std::unique_ptr<Item> alchohol;   
    
public:
    uint8_t alchohol_meter;

    Hobo(const std::string name);
    Zoo* getZoo() const;
    // Item* getItems() const;
    // void addItem(Item *item);
    // void useItem(Item *item);   
    void addCreature();
    void drinkAlchohol();
    virtual Move* chooseAction();
    virtual ~Hobo();
};

#endif
