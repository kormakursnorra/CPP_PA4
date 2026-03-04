#ifndef ENTITY_H
#define ENTITY_H

#include "move.h"
#include <string>
#include "status.h"

class Entity {
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
    Entity(std::string name, int hp, int attack, int defense, int speed);

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

    virtual Move* chooseAction() = 0; // virtual shits dawg
    virtual ~Entity() {}
};
#endif
