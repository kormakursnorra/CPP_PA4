#ifndef CREATURE_H
#define CREATURE_H

#include "creatures/move.h"

#include <string>
#include <cstdint>

class Creature {
protected:
    std::string name;
    uint8_t hp;
    uint8_t maxHp;
    uint8_t attack;
    uint8_t defense;
    uint8_t speed;
    Move moves[4];
    uint8_t moveCount;
    Status status;
    uint8_t statusDuration;


public:
    Creature(std::string name, uint8_t hp, 
        uint8_t attack, uint8_t defense, uint8_t speed
    );

    bool operator==(const Creature &other) const;

    void takeDamage(uint8_t dmg);
    bool isAlive() const;
    void displayStatus() const;
    void displayMoves() const;
    void addMove(Move move);
    void setStatus(Status s, uint8_t duration);
    void applyStatusEffect();
    std::string getStatusName() const;

    std::string getName() const;
    uint8_t getSpeed() const;
    uint8_t getAttack() const;
    uint8_t getDefense() const;
    Status getStatus() const;

    virtual Move* chooseAction() = 0; // virtual shits dawg
    virtual ~Creature() {}
};

#endif
