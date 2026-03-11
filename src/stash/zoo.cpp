#include <cassert>

#include "zoo.h"
#include "creatures/creature.h"

Zoo::Zoo(const Hobo *zooKeeper, std::string name) 
: Stash<Zoo, Creature*>(zooKeeper), name(name), numAlive(0) {}


void Zoo::onInsert(Creature *creature) {
    if (numContents == 1) { starter = creature; }
    numAlive++;
}

void Zoo::onRemove(Creature *creature) {
    
    if (starter == creature) { starter = nullptr; }
    numAlive--;
}

Creature* Zoo::getStarter(const Hobo *zooKeeper) const {
    assert(isOwner(zooKeeper));
    return starter;
}

std::string Zoo::getName(const Hobo *zooKeeper) const {
    assert(isOwner(zooKeeper));
    return name;
}

int Zoo::getNumAlive(const Hobo *zooKeeper) const {
    assert(isOwner(zooKeeper));
    return numAlive;
}

bool Zoo::changeStarter(const Hobo *zooKeeper, int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isInStash(creatureKey));
    
    Creature *creature = contents.at(creatureKey);
    starter = creature;
    return true;
}

bool Zoo::updateStatus(const Hobo *zooKeeper,  int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isInStash(creatureKey));
        
    Creature *creature = contents.at(creatureKey);
    
    if (creature->isAlive()) {
        numAlive++;
    } else {
        assert(numAlive != 0);
        numAlive--;
    }
    
    return true;
}