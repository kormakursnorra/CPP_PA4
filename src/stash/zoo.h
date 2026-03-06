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
    void onInsert(Creature *creature) override;
    void onRemove(Creature *creature) override;

public:
    std::string name;
    int numAlive;

    Zoo(const Hobo *zooKeeper, std::string zooName);
    bool changeStarter(const Hobo *zooKeeper, int creatureKey);
    bool updateStatus(const Hobo *zooKeeper, int creatureKey);
    int getNumAlive(const Hobo *zooKeeper) const;
    ~Zoo();

    friend class Battle;
};

#endif