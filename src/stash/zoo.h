#ifndef ZOO_H
#define ZOO_H

#include <sys/types.h>

#include "stash.h"
#include "creatures/creature.h"

class Zoo : public Stash<Zoo, Creature*> {
private:
    const Hobo *zooKeeper;
    Creature *starter;
    
protected:
    std::string name;
    int numAlive;
    
    void onInsert(Creature *creature);
    void onRemove(Creature *creature);

public:
    Zoo(const Hobo *zooKeeper, std::string zooName);
    Creature* getStarter(const Hobo *zooKeeper) const;
    std::string getName(const Hobo *zooKeeper) const; 
    int getNumAlive(const Hobo *zooKeeper) const;
    bool changeStarter(const Hobo *zooKeeper, int creatureKey);
    bool updateStatus(const Hobo *zooKeeper, int creatureKey);
    ~Zoo();
};

#endif