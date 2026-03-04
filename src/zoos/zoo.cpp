#include "zoo.h"
#include "hobos/hobo.h"
#include "creatures/creature.h"


Zoo::Zoo(const Hobo *zooKeeper, std::string name) 
: zooKeeper(zooKeeper), name(name) {}

bool Zoo::isOwner(const Hobo* caller) const {
    return caller == zooKeeper; 
}

bool Zoo::insertNewMember(const Hobo *zooKeeper, Creature *creature) {
    if (!isOwner(zooKeeper) || 
        creatures.find(creature) == creatures.end()
    ) {
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
    if (!isOwner(zooKeeper) || 
        creatures.find(creature) == creatures.end()
    ) {
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
    if (!isOwner(zooKeeper) || 
        creatures.find(creature) == creatures.end()
    ) {
        return false;
    }
    
    if (starter != creature) {
        starter = creature;
    }
    
   return true;
}

bool Zoo::updateStatus(const Hobo *zooKeeper, Creature *creature) {
    if (!isOwner(zooKeeper) || 
        creatures.find(creature) == creatures.end()
    ) {
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

int Zoo::getNumMembers(const Hobo *zooKeeper) {
    if (!isOwner(zooKeeper)) {
        return -1;
    } return numMembers;
}

int Zoo::getNumAlive(const Hobo *zooKeeper) {
    if (!isOwner(zooKeeper)) {
        return -1;
    } return numAlive;
}


Zoo::~Zoo() {
    
}