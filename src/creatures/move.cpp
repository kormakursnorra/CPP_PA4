#include <cstdlib>
#include <iostream>

#include "move.h"

Move::Move() : name(""), power(0), accuracy(100),
 effect(NONE), effectChance(0), effectDuration(0) {}

Move::Move(std::string name, int power, int accuracy, 
    Status effect, int effectChance, int effectDuration
)
    : name(name), power(power), accuracy(accuracy), 
    effect(effect), effectChance(effectChance), effectDuration(effectDuration) {}

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

int Move::getAccuracy() const {
    return accuracy;
}

int Move::getEffectDuration() const {
    return effectDuration;
}