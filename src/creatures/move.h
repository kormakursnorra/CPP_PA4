#ifndef MOVE_H
#define MOVE_H

#include "status.h"
#include <string>

class Move {
private:
    std::string name;
    int power;
    int accuracy; // 0-100 chance to hit
    Status effect;
    int effectChance;
    int effectDuration;

public:
    Move();
    Move(std::string name, int power, int accuracy, Status effect, int effectChance, int effectDuration = 0);

    std::string getName() const;
    int getPower() const;
    bool hits() const;
    void display() const;
    Status getEffect() const;
    int getEffectChance() const;
    int getAccuracy() const;
    int getEffectDuration() const;
};

#endif
