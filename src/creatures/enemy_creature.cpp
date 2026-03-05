#include "creatures/enemy_creature.h"
#include <cstdint>
#include <cstdlib>
// #include <iostream>

EnemyCreature::EnemyCreature(std::string name, uint8_t hp, 
    uint8_t attack, uint8_t defense, uint8_t speed
) : Creature(name, hp, attack, defense, speed) {}

// Move* EnemyCreature::nextAction() {
//     int choice = rand() % moveCount;
//     std::cout << getName() << " is thinking...\n";
//     return &moves[choice];
// }
