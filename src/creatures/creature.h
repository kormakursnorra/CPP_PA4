#ifndef CREATURE_H
#define CREATURE_H

#include "creatures/move.h"

#include <string>
#include <cstdint>

class Creature {
protected:
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    Move moves[4];
    int moveCount;
    Status status;
    int statusDuration;


public:
    Creature(std::string name, int hp, 
        int attack, int defense, int speed
    );

    bool operator==(const Creature &other) const;

    void takeDamage(int dmg);
    bool isAlive() const;
    void displayStatus() const;
    void displayMoves() const;
    void addMove(Move move);
    void setStatus(Status s, int duration);
    void applyStatusEffect();
    std::string getStatusName() const;

    std::string getName() const;
    int getSpeed() const;
    int getAttack() const;
    int getDefense() const;
    Status getStatus() const;
    Move* getMove(int moveKey);

    virtual ~Creature() {}
};

#endif
