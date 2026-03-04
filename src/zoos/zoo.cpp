#include "zoo.h"
#include "hobos/hobo.h"
#include "creatures/creature.h"
#include <cassert>


Zoo::Zoo(const Hobo *zooKeeper, std::string name) 
: zooKeeper(zooKeeper), name(name) {}

bool Zoo::isOwner(const Hobo* caller) const {
    return caller == zooKeeper; 
}

bool Zoo::insertNewMember(const Hobo *zooKeeper, Creature *creature) {
    assert(isOwner(zooKeeper));
    
    if (creatures.find(creature) == creatures.end()) {
        return false;
    }

    creatures.insert({creature, 1});
    if (starter == nullptr) {
        starter = creature; 
    }

    numMembers++;
    numAlive++;
    return true;
}

bool Zoo::removeMember(const Hobo *zooKeeper, Creature *creature) {
    assert(isOwner(zooKeeper));

    if (creatures.find(creature) == creatures.end()) {
        return false;
    }
    
    if (starter == creature) { 
        starter = nullptr;
    }

    numMembers--;
    numAlive--;
    return true;
}

bool Zoo::changeStarter(const Hobo *zooKeeper, Creature *creature) {
    assert(isOwner(zooKeeper));
    
    if (creatures.find(creature) == creatures.end()) {
        return false;
    }
    
    if (starter != creature) {
        starter = creature;
    }
    
   return true;
}

bool Zoo::updateStatus(const Hobo *zooKeeper, Creature *creature) {
    assert(isOwner(zooKeeper));
    
    if (creatures.find(creature) == creatures.end()) {
        return false;
    }
    
    int memberStatus = creatures.at(creature);
    if (memberStatus == 0) { 
        memberStatus = 1;
        numAlive--; 
    } else { 
        memberStatus = 0;
        numAlive--; 
    }
    creatures.at(creature) = memberStatus;
    return true;

}

uint8_t Zoo::getNumMembers(const Hobo *zooKeeper) {
    assert(isOwner(zooKeeper));
    return numMembers;
}

uint8_t Zoo::getNumAlive(const Hobo *zooKeeper) {
    assert(!isOwner(zooKeeper));
    return numAlive;
}


Zoo::~Zoo() {
    
}