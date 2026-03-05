#ifndef ENEMY_ZOO_H
#define ENEMY_ZOO_H

#include "zoos/zoo.h"

#include <sys/types.h>
#include <unordered_map>
#include <cstdint>


class EnemyZoo : public Zoo {
public:
    EnemyZoo(const Hobo *zooKeeper, std::string name);
    
};

#endif