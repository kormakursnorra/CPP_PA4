#include "creatures/creature.h"
#include <iostream>

Creature::Creature(
    std::string name, int hp, int attack, int defense, int speed
) : name(name), hp(hp), maxHp(hp), attack(attack),
    defense(defense), speed(speed), moveCount(0),
    status(NONE), statusDuration(0) {}

bool Creature::operator==(const Creature &other) const {
    return (name == other.name);
}

void Creature::takeDamage(int dmg) {
    int actual = (int)(((rand() % 5) + dmg) * (100 - defense) / 100);
    if (actual < 1) {
        actual = 1;
    }
    hp -= actual;
    if (hp < 0) {
        hp = 0;
    }
}

bool Creature::isAlive() const {
    return hp > 0;
}

void Creature::displayStatus() const {
    std::cout << name << " (" << hp << "/" << maxHp << ")";
}

void Creature::displayMoves() const {
    for (int i = 0; i < moveCount; i++) {
        std::cout << i + 1 << ". ";
        moves[i].display();
    }
}

void Creature::addMove(Move move) {
    if (moveCount <4) {
        moves[moveCount] = move;
        moveCount++;
    }
}

void Creature::setStatus(Status s, int duration) {
    if (status != NONE) {
        return;
    }
    status = s;
    statusDuration = duration;
    std::cout << name << " is now " << getStatusName() << "!\n";
}

std::string Creature::getStatusName() const {
    switch (status) {
        case INFECTED: return "Infected";
        case STUNNED: return "stunned";
        case BURNED: return "Burned";
        default: return "Fine";
    }

}

void Creature::applyStatusEffect() {
    if (status == NONE) {
        return;
    }

    switch (status) {
        case INFECTED: {
            int dmg = maxHp * 0.10;
            hp -= dmg;
            if (hp < 0) {
                hp = 0;
            }
            std::cout << name << " is infected and lost " << dmg << "HP!\n";
            break; 
        }
        case STUNNED: {
            std::cout << name << " is stunned and cant move!\n";
            break; 
        }
        case BURNED: {
            int bdmg = maxHp * 0.05;
            hp -= bdmg;
            if (hp < 0) {
                hp = 0;
            }
            std::cout << name << " is burning and lost " << bdmg << "HP!\n";
            break; 
        }
        default: 
            break;
    }

    statusDuration--;
    if (statusDuration <= 0) {
        std::cout << name << " recovered from" << getStatusName() << "!\n";
        status = NONE;
        statusDuration = 0;
    }
}

std::string Creature::getName() const {
    return name;
}

int Creature::getSpeed() const {
    return speed;
}

int Creature::getAttack() const {
    return attack;
}

int Creature::getDefense() const {
    return defense;
}

Status Creature::getStatus() const {
    return status;
}
