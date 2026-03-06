#include "hobos/hobo.h"
#include "creatures/creature.h"

#include <string>
#include <memory>
#include <vector>


const std::string randEnemyName(uint8_t randNum) {
    return "Enemy Hobo " + std::to_string(randNum);
}

const std::string randZooName(uint8_t randNum) {
    return "Enemy Zoo " + std::to_string(randNum);
}

Hobo::Hobo(const std::string name, std::string zooName) 
: name(name), alchohol_meter(0) {
    zoo = std::make_unique<Zoo>(this, zooName);
    numCreatures = zoo->getNumContents(this);
    // inventory = Inventory;
    // booze = std::unique_ptr<Item>( 
        // new Item(this, zooName)
    // );
    // numItems = zoo->getNumContents(this);
}

Zoo& Hobo::getZoo() const {
    return *zoo;
};

// Inventory& Hobo::getInventory() const {
//     return *inventory;
// };

std::string Hobo::getName() const {
    return name;
}

int Hobo::getNumCreatures() const {
    return zoo->getNumContents(this);
}

// int Hobo::getNumItems() const {
//     return inventory->getNumContents(this);
// }

void Hobo::addCreature(Creature *creature) {
    zoo->insert(this, creature);
}

// void Hobo::addItem(Item *item) {
//     inventory->insert(this, item);
// }

void Hobo::drinkAlchohol() {
    return;
}
