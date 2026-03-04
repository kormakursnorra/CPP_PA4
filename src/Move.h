#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
private:
    std::string name;
    int power;
    int accuracy; // 0-100 chance to hit

public:
    Move();
    Move(std::string name, int power, int accuracy);

    std::string getName() const;
    int getPower() const;
    bool hits() const;
    void display() const;
};

#endif
