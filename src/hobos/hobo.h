#ifndef HOBO_H
#define HOBO_H

#include "zoos/zoo.h"
// #include "items.h"

#include <string>
#include <memory>



class Hobo {
private:
    const std::string name;
    std::unique_ptr<Zoo> zoo;
    // std::unique_ptr<Item> *item;   

public:

    Hobo(std::string name);
    Zoo* getZoo() const;
    // Item* getItem() const;
    void selectCreature();
    // void addItem(Item *item);   
    virtual ~Hobo();
};

#endif
