#include <string>
#include <memory>
#include <vector>

#include "hobo.h"
#include "battle.h" 
#include "actions.h"
#include "items/item.h"
#include "items/booze.h"
#include "creatures/creature.h"


const std::string randEnemyName(uint8_t randNum) {
    return "Enemy Hobo " + std::to_string(randNum);
}

const std::string randZooName(uint8_t randNum) {
    return "Enemy Zoo " + std::to_string(randNum);
}

Hobo::Hobo(const std::string name, std::string zooName) 
: name(name), alchoholMeter(0) {
    zoo = std::make_unique<Zoo>(this, zooName);
    inventory = std::make_unique<Inventory>(this);
    booze = std::make_unique<Booze>(
        "Booze", 
        "Increases Creature attack stats for all Zoo Members at the cost of an increased likelihood they flee",
        0, EMPOWER); 
    
    numCreatures = zoo->getNumContents(this);
    numItems = inventory->getNumContents(this);
}

std::string Hobo::getName() const {
    return name;
}

Zoo& Hobo::getZoo() const {
    return *zoo.get();
};

Creature* Hobo::getCreature(int creatureKey) const {
    return zoo->getStashItem(this, creatureKey);
};

Creature* Hobo::getStarter() const {
    return zoo->getStarter(this);
}

int Hobo::getNumCreatures() const {
    return zoo->getNumContents(this);
}

void Hobo::addCreature(Creature *creature) {
    zoo->insert(this, creature);
}

Inventory& Hobo::getInventory() const {
    return *inventory.get();
}

Item* Hobo::getItem(int itemKey) const {
    return inventory->getStashItem(this, itemKey);
}

Booze* Hobo::getBooze() const {
    return booze.get();
}

int Hobo::getNumItems() const {
    return inventory->getNumContents(this);
}

int Hobo::getNumGroupedItems(int itemKey) const {
    Item *item = inventory->getStashItem(this, itemKey);
    return inventory->getNumGroupedItems(item);
}

void Hobo::addItem(Item *item) {
    inventory->insert(this, item);
}

void Hobo::resetChoiceContext() {
    _choiceCtx = ChoiceContext{};
}

const ChoiceContext& Hobo::getChoiceContext() const { 
    return _choiceCtx; 
}

const Action& Hobo::getLastAction() const {
    return _lastAction;
}

CreatureInfo Hobo::makeCreatureInfo(Creature *creature, bool isActive) {
    CreatureInfo info;
    info.name       = creature->getName();
    info.hp         = creature->getHp();
    info.maxHp      = creature->getMaxHp();
    info.attack     = creature->getAttack();
    info.defense    = creature->getDefense();
    info.speed      = creature->getSpeed();
    info.status     = creature->getStatus();
    info.statusName = creature->getStatusName();
    info.alive      = creature->isAlive();
    info.isActive   = isActive;

    for (int i = 0; i <= 3; ++i) {
        Move* move = creature->getMove(i);
        if (!move) { continue; }
        MoveInfo moveInfo;
        moveInfo.name         = move->getName();
        moveInfo.power        = move->getPower();
        moveInfo.effect       = move->getEffect();
        moveInfo.accuracy     = move->getAccuracy();
        moveInfo.effectChance = move->getEffectChance();
        moveInfo.effectDuration = move->getEffectDuration();
        info.moves.push_back(moveInfo);
    }

    return info;
}

ItemInfo Hobo::makeItemInfo(Item *item) {
    ItemInfo info;
    info.name        = item->getItemName();
    info.description = item->getItemDescription();
    info.type        = item->getItemType();
    info.effect      = item->getItemEffect();
    return info;
}

BoozeInfo Hobo::makeBoozeInfo(Booze *drink) {
    BoozeInfo info;
    info.sipsLeft           = drink->getSipsLeft();
    info.attackBoost        = drink->getItemEffect();
    info.fleeChanceIncrease = this->alchoholMeter * 25;
    return info;
}

std::vector<CreatureInfo> Hobo::makeZooInfo() {
    std::vector<CreatureInfo> zooInfo;
    auto *stash = zoo->getStash(this);
    for (auto &[key, creature] : *stash) {
        zooInfo.push_back(makeCreatureInfo(creature));
    }
    return zooInfo;
}

std::vector<ItemInfo> Hobo::makeInventoryInfo() {
    std::vector<ItemInfo> inventoryInfo;
    auto *stash = inventory->getStash(this);
    for (auto &[key, item] : *stash) {
        inventoryInfo.push_back(makeItemInfo(item));
    }
    return inventoryInfo;
}


Hobo::~Hobo() {}
