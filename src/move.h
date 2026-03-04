#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "status.h"

class Move {
private:
    std::string name;
    int power;
    int accuracy; // 0-100 chance to hit
    Status effect;
    int effectChance;

public:
    Move();
    Move(std::string name, int power, int accuracy, Status effect, int effectChance);

    std::string getName() const;
    int getPower() const;
    bool hits() const;
    void display() const;
    Status getEffect() const;
    int getEffectChance() const;
};

#endif
