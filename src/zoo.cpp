#include "zoo.h"
#include "hobos/player.h"
#include "creature.h"
#include <stdexcept>


Zoo::Zoo(const Player *player) : player(player) {}

int Zoo::insertNewMember(const Player *player, Creature *creature) {
    if (this->player != player) {
        return 0;
    }

    if (creatureMembers.find(creature) == creatureMembers.end()) {
        return 0;
    }
    
    creatureMembers.insert({creature, 1});
    if (starter == nullptr) {
        starter = creature; 
    }

    numMembers++;
    numAlive++;
    return 1;
}

int Zoo::removeMember(const Player *player, Creature *creature) {
    if (this->player != player) {
        return 0;
    }
 
    if (creatureMembers.erase(creature) == 0) {
        return 0;
    }
    
    if (starter == creature) { 
        starter = nullptr;
    }

    numMembers++;
    numAlive++;
    return 1;
}

int Zoo::changeStarter(const Player *player, Creature *creature) {
    if (this->player != player) {
        return 0;
    }

    if (creatureMembers.find(creature) == creatureMembers.end()) {
        return 0;
    }
    
    if (starter != creature) {
        starter = creature;
    }
    
   return 1;
}

int Zoo::updateStatus(const Player *player, Creature *creature) {
    if (this->player != player) {
        return 0;
    }
    
    try {
        int memberStatus = creatureMembers.at(creature);
        if (memberStatus == 0) { 
            memberStatus = 1; 
        } else { 
            memberStatus = 0; 
        }
        creatureMembers.at(creature) = memberStatus;
        return 1;

    } catch (std::out_of_range e) {
        return 0;
    }


}

Zoo::~Zoo() {
    
}