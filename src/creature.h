#ifndef CREATURE_H
#define CREATURE_H

#include "entity.h"

#include <functional>

class Creature : public Entity {
public:
    Creature(std::string name, int hp, int attack, int defense, int speed);

    bool operator==(const Creature &other);
    ~Creature();
};

namespace std {
    template <> struct hash<Creature> {
        size_t operator()(const Creature &creature) const {
            size_t hash_name = hash<std::string>{}(creature.getName());
            return hash_name;
        }
    };
}

#endif