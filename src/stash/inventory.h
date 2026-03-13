#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>

#include "stash.h"
#include "items/item.h"


class Inventory : public Stash<Inventory, Item*> {
private:
    const Hobo *inventoryKeeper;

protected:
    using NumGroupedItems = std::unordered_map<Item*, int>; 
    NumGroupedItems numGroupedItems;
    
    void onInsert(Item *item);
    void onRemove(Item *item);
    
    public:
    Inventory(const Hobo *inventoryKeeper);
    int decrementNumItems(Item *item);
    int getNumGroupedItems(Item *item) const;
    
    friend class Stash<Inventory, Item*>;
};

#endif
