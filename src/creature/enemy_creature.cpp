#include "creature/enemy_creature.h"
#include <cstdlib>
#include <iostream>

EnemyCreature::EnemyCreature(std::string name, int hp, int attack, int defense, int speed)
    : Creature(name, hp, attack, defense, speed) {}

Move* EnemyCreature::nextAction() {
    int choice = rand() % moveCount;
    std::cout << getName() << " is thinking...\n";
    return &moves[choice];
}
