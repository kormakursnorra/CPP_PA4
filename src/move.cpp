#include "move.h"
#include <cstdlib>
#include <iostream>

Move::Move() : name(""), power(0), accuracy(100) {}

Move::Move(std::string name, int power, int accuracy, Status effect, int effectChance)
    : name(name), power(power), accuracy(accuracy),
    effect(effect), effectChance(effectChance) {}

std::string Move::getName() const {
    return name;
}

int Move::getPower() const {
    return power;
}

bool Move::hits() const {
    return (rand() % 100) < accuracy;
}

void Move::display() const {
     std::cout << name << " (power: " << power <<  ")" << std::endl;
}

Status Move::getEffect() const {
    return effect;
}

int Move::getEffectChance() const {
    return effectChance;
}