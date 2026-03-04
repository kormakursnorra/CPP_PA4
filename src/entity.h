#ifndef ENTITY_H
#define ENTITY_H

#include "Move.h"
#include <string>

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


public:
    Entity(std::string name, int hp, int attack, int defense, int speed);

    void takeDamage(int dmg);
    bool isAlive() const;
    void displayStatus() const;
    void displayMoves() const;
    void addMove(Move move);

    std::string getName() const;
    int getSpeed() const;
    int getAttack() const;
    int getDefense() const;

    virtual Move* chooseAction() = 0; // virtual shits dawg
    virtual ~Entity() {}
};
#endif
