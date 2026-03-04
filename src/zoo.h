#ifndef ZOO_H
#define ZOO_H

#include "hobos/player.h"
#include "creature.h"

#include <unordered_map>

typedef std::unordered_map<Creature *, int> CreatureStatusMap;

class Zoo {
public:
    const Player *player;
    static CreatureStatusMap creatureMembers; // Status -> 0: dead 1: alive
    static Creature *starter;
    int numMembers;
    int numAlive;

    Zoo(const Player *player);
    int insertNewMember(const Player *player, Creature *creature);
    int removeMember(const Player *player, Creature *creature);
    int changeStarter(const Player *player, Creature *creature);
    int updateStatus(const Player *player, Creature *creature);
    ~Zoo();
};

#endif