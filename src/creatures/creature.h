#ifndef CREATURE_H
#define CREATURE_H

#include "move.h"

#include <string>

struct Stats {
    int hp;
    int speed;
    int attack;
    int defense;

    int maxHp;
    int maxSpeed;
    int maxAttack;
    int maxDefense;
};

class Creature {
protected:
    std::string name;
    Stats stats;
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
    int getHp() const;
    int getMaxHp() const;
    int getSpeed() const;
    int getMaxSpeed() const;
    int getAttack() const;
    int getMaxAttack() const;
    int getDefense() const;
    int getMaxDefense() const;
    Status getStatus() const;
    Move* getMove(int moveKey) const;
    void setHp(int newHp);
    void setAttack(int newAttack);
    void setDefence(int newDefence);
    void setSpeed(int newSpeed);

    virtual ~Creature() {}
};

#endif
