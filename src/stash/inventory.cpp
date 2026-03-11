#include "inventory.h"


Inventory::Inventory(const Hobo* inventoryKeeper)
: Stash<Inventory, Item*>(inventoryKeeper) {}

void Inventory::onInsert(Item *item) {
    int numItems = 0;
    if (numGroupedItems.count(item) == 0) {
        numGroupedItems.insert({item, numItems + 1});      
    }
    numItems = numGroupedItems.at(item);
    numGroupedItems.insert({item, numItems + 1});
}

void Inventory::onRemove(Item *item) {
    numGroupedItems.erase(item);
}

void Inventory::decrementNumItems(Item *item) {
    numGroupedItems.at(item)--;
    // int numItems = 
    // if (numItems == 0) {
    //     this->remove(inventoryKeeper, item);
    // }
}


int Inventory::getNumGroupedItems(Item *item) const {
    return numGroupedItems.at(item);
}