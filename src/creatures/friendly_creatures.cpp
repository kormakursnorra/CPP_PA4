#include "creatures/friendly_creatures.h"

#include <cstdlib>
#include <iostream>

FriendlyCreature::FriendlyCreature(std::string name, int hp, int attack, int defense, int speed)
    : Creature(name, hp, attack, defense, speed) {}

Move* FriendlyCreature::nextAction() {
    int choice = rand() % moveCount;
    std::cout << getName() << " is thinking...\n";
    return &moves[choice];
}
