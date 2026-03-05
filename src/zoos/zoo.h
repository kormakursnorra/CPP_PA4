#ifndef ZOO_H
#define ZOO_H

#include "creatures/creature.h"

#include <sys/types.h>
#include <unordered_map>

class Hobo;
class Battle;

typedef std::unordered_map<int, Creature *> CreatureMap;

class Zoo {
private:
    const Hobo* zooKeeper;
    CreatureMap creatures;
    Creature *starter;
    int maxMembers;
    
    bool isOwner(const Hobo* caller) const;
    bool isMember(int creatureKey) const;
    
public:
    std::string name;
    int numMembers;
    int numAlive;

    Zoo(const Hobo *zooKeeper, std::string zooName);
    CreatureMap* getZoo(const Hobo *zooKeeper);
    Creature* getCreature(const Hobo *zooKeeper, int creatureKey);
    bool insertNewMember(const Hobo *zooKeeper, Creature *creature);
    bool removeMember(const Hobo *zooKeeper, int creatureKey);
    bool changeStarter(const Hobo *zooKeeper, int creatureKey);
    bool updateStatus(const Hobo *zooKeeper, int creatureKey);
    int getNumMembers(const Hobo *zooKeeper);
    int getNumAlive(const Hobo *zooKeeper);
    ~Zoo();

    friend class Battle;
};

#endif