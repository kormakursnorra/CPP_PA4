#ifndef ZOO_H
#define ZOO_H

#include "creatures/creature.h"
#include "stash/stash.h"

#include <sys/types.h>

class Zoo : public Stash<Creature*> {
private:
    const Hobo *zooKeeper;
    Creature *starter;
    
protected:
    std::string name;
    int numAlive;
    
    void onInsert(Creature *creature) override;
    void onRemove(Creature *creature) override;

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