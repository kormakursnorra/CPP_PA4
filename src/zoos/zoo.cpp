#include "zoos/zoo.h"
#include "creatures/creature.h"
#include <cassert>


Zoo::Zoo(const Hobo *zooKeeper, std::string name) 
: zooKeeper(zooKeeper), name(name) {
    maxMembers = 6;
    numMembers = 0;
    numAlive = 0;
}


bool Zoo::isOwner(const Hobo* caller) const {
    return caller == zooKeeper; 
}

bool Zoo::isMember(int creatureKey) const {
    return creatures.count(creatureKey) > 0; 
}

Creature* Zoo::getCreature(const Hobo *zooKeeper, int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isMember(creatureKey));

    return creatures.at(creatureKey);
}

CreatureMap* Zoo::getZoo(const Hobo *zooKeeper) {
    assert(isOwner(zooKeeper));
    return &creatures;
}

bool Zoo::insertNewMember(const Hobo *zooKeeper, Creature *creature) {
    assert(isOwner(zooKeeper));
    
    if (numMembers == maxMembers) { 
        return false; 
    }
    
    creatures.insert(
        {numMembers + 1, creature}
    );

    numMembers++;
    numAlive++;
    return true;
}

bool Zoo::removeMember(const Hobo *zooKeeper, int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isMember(creatureKey));

    creatures.erase(creatureKey);

    assert(creatures.count(creatureKey) == 0);

    numMembers--;
    numAlive--;
    return true;
}

bool Zoo::changeStarter(const Hobo *zooKeeper, int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isMember(creatureKey));
    
    Creature *creature = creatures.at(creatureKey);
    if (creature != starter) {
        starter = creature;
    };

    return true;
}

bool Zoo::updateStatus(const Hobo *zooKeeper,  int creatureKey) {
    assert(isOwner(zooKeeper));
    assert(isMember(creatureKey));
        
    Creature *creature = creatures.at(creatureKey);
    
    if (creature->isAlive()) {
        numAlive++;
    } else {
        assert(numAlive != 0);
        numAlive--;
    }
    
    return true;
}


int Zoo::getNumMembers(const Hobo *zooKeeper) {
    assert(!isOwner(zooKeeper));
    return numMembers;
}

int Zoo::getNumAlive(const Hobo *zooKeeper) {
    assert(!isOwner(zooKeeper));
    return numAlive;
}


Zoo::~Zoo() {
    
}