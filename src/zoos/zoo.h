#ifndef ZOO_H
#define ZOO_H

#include "creatures/creature.h"

#include <memory>
#include <unordered_map>

class Hobo;

typedef std::unordered_map<Creature *, int> CreatureStatusMap;

class Zoo {
private:
    const Hobo* zooKeeper;
    CreatureStatusMap creatures; // Status -> 0: dead 1: alive
    Creature *starter;
    
    bool isOwner(const Hobo* caller) const;
    
public:
    std::string name;
    int numMembers;
    int numAlive;

    Zoo(const Hobo *player, std::string name);
    Creature *getCreature(const Hobo *player);
    bool insertNewMember(const Hobo *player, Creature *creature);
    bool removeMember(const Hobo *player, Creature *creature);
    bool changeStarter(const Hobo *player, Creature *creature);
    bool updateStatus(const Hobo *player, Creature *creature);
    int getNumMembers(const Hobo *player);
    int getNumAlive(const Hobo *player);
    ~Zoo();
};

#endif