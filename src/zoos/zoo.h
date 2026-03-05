#ifndef ZOO_H
#define ZOO_H

#include "creatures/creature.h"

#include <sys/types.h>
#include <unordered_map>
#include <cstdint>

class Hobo;

typedef std::unordered_map<uint8_t, Creature *> CreatureMap;

class Zoo {
private:
    const Hobo* zooKeeper;
    CreatureMap creatures;
    Creature *starter;
    uint8_t maxMembers;
    
    bool isOwner(const Hobo* caller) const;
    bool isMember(uint8_t creatureKey) const;
    
public:
    std::string name;
    uint8_t numMembers;
    uint8_t numAlive;

    Zoo(const Hobo *zooKeeper, std::string name);
    CreatureMap* getZoo(const Hobo *zooKeeper);
    Creature* getCreature(const Hobo *zooKeeper, uint8_t creatureKey);
    bool insertNewMember(const Hobo *zooKeeper, Creature *creature);
    bool removeMember(const Hobo *zooKeeper, uint8_t creatureKey);
    bool changeStarter(const Hobo *zooKeeper, uint8_t creatureKey);
    bool updateStatus(const Hobo *zooKeeper, uint8_t creatureKey);
    uint8_t getNumMembers(const Hobo *zooKeeper);
    uint8_t getNumAlive(const Hobo *zooKeeper);
    ~Zoo();
};

#endif