#include <string>
#include <memory>

#include "hobo.h"
#include "actions.h"
#include "creatures/creature.h"
#include "battle.h" 


const std::string randEnemyName(uint8_t randNum) {
    return "Enemy Hobo " + std::to_string(randNum);
}

const std::string randZooName(uint8_t randNum) {
    return "Enemy Zoo " + std::to_string(randNum);
}

Hobo::Hobo(const std::string name, std::string zooName) 
: name(name), alchoholMeter(0) {
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

Creature* Hobo::getCreature(int creatureKey) const {
    return zoo->getStashItem(this, creatureKey);
};

Creature* Hobo::getStarter() const {
    return zoo->getStarter(this);
}

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

    for (int i = 1; i <= 4; ++i) {
        Move* move = creature->getMove(i);
        if (!move) { continue; }
        MoveInfo moveInfo;
        moveInfo.name         = move->getName();
        moveInfo.power        = move->getPower();
        moveInfo.effect       = move->getEffect();
        moveInfo.accuracy     = move->getAccuracy();
        moveInfo.effectChance = move->getEffectChance();
        info.moves.push_back(moveInfo);
    }

    return info;
}

Info<CreatureInfo> Hobo::makeZooInfo() {
    std::vector<CreatureInfo> zooInfo;
    auto *stash = zoo->getStash(this);
    for (auto &[key, creature] : *stash) {
        zooInfo.push_back(makeCreatureInfo(creature));
    }
    return zooInfo;
}

Hobo::~Hobo() {}
