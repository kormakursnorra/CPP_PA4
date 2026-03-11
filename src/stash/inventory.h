#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>

#include "stash.h"
#include "items/item.h"

template <typename ItemType>
class Inventory : public Stash<Inventory<Item<ItemType>>, Item<ItemType>*> {
private:
    const Hobo *inventoryKeeper;

protected:
    using NumGroupedItems = std::unordered_map<Item<ItemType>*, int>; 
    NumGroupedItems numGroupedItems;
    
    void onInsert(Item<ItemType> *item) {
        int numItems = 0;
        if (numGroupedItems.count(item) == 0) {
            numGroupedItems.insert({item, numItems + 1});      
        }
        numItems = numGroupedItems.at(item);
        numGroupedItems.insert({item, numItems + 1});
    }
    
    void onRemove(Item<ItemType> *item) {
        
        numGroupedItems.at(item)--;
    }
    
public:
    Inventory(const Hobo *inventoryKeeper)
    : Stash<Inventory, Item<ItemType>*>(inventoryKeeper) {};
};

#endif
