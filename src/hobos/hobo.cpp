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

Hobo::Hobo(const std::string name, std::string zooName) : name(name) {
    zoo = upZoo(new Zoo(this, zooName));
    numCreatures = zoo->getNumMembers(this);
    // items = Inventory;
    // booze = std::unique_ptr<Item>( 
        // new Item(this, zooName)
    // );
    // numItems = zoo->getNumMembers(this);
    alchohol_meter = 0;
}

upZoo& Hobo::getZoo() {
    return zoo;
};

void Hobo::addCreature() {
    // Creature *newCreature = new Creature();
    return;
}

void Hobo::drinkAlchohol() {
    return;
}

