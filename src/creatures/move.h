#ifndef MOVE_H
#define MOVE_H

#include "creatures/status.h"
#include <string>

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
};

#endif
