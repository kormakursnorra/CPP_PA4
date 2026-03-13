#include <iostream>

#include "creatures/creature.h"

Creature::Creature(
    std::string name, int hp, int attack, int defense, int speed
) : name(name), stats {
    hp, speed, attack, defense, 
    hp, speed, attack, defense}, moveCount(0),
    status(NONE), statusDuration(0) {}

bool Creature::operator==(const Creature &other) const {
    return (name == other.name);
}

void Creature::takeDamage(int dmg) {
    int &defense = stats.defense;
    int &hp = stats.hp;

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
    return stats.hp > 0;
}

void Creature::displayStatus() const {
    int hp = stats.hp;
    int maxHp = stats.maxHp;
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
}

std::string Creature::getStatusName() const {
    switch (status) {
        case INFECTED: return "Infected";
        case STUNNED: return "stunned";
        case BURNED: return "Burned";
        case POISONED: return "Poisoned";
        case BLEEDING: return "Bleeding";
        case WEAKENED: return "Weakened";
        case DEVINE: return "Devine";
        case SCARED: return "Scared";
        default: return "Fine";
    }

}

std::string Creature::applyStatusEffect() {
    if (status == NONE) {
        return "";
    }
    std::string msg;

    int &maxHp = stats.hp;
    int &hp = stats.hp;

    switch (status) {
        case INFECTED: {
            int dmg = maxHp * 0.10;
            hp = std::max(0, hp - dmg);
            msg = name + " is infected and lost " + std::to_string(dmg) + " HP!";
            break; 
        }
        case STUNNED: {
            msg = name + " is stunned and cant move!";
            break; 
        }
        case BURNED: {
            int dmg = maxHp * 0.05;
            hp = std::max(0, hp - dmg);
            msg = name + " is burning and lost " + std::to_string(dmg) + " HP!";
            break; 
        }
        case POISONED: {
            int dmg = maxHp * 0.15;
            hp -= dmg;
            msg = name + " is badly poisoned and lost " + std::to_string(dmg) + " HP!";
            break;
        }
        case BLEEDING: {
            int dmg = maxHp * 0.10;
            hp -= dmg;
            msg = name + " is bleeding and lost" + std::to_string(dmg) + " HP!";
            break;
        }
        case WEAKENED: {
            msg = name + " is weakened!";
            break;
        }
        case SCARED: {
            msg = name + " is terrified!";
            break;
        }
        default: 
            break;
    }

    statusDuration--;
    if (statusDuration <= 0) {
        msg =  "\n " + name + " recovered from" + getStatusName() + "!";
        status = NONE;
        statusDuration = 0;
    }
    return msg;
}

std::string Creature::getName() const {
    return name;
}

int Creature::getHp() const {
    return stats.hp;
}

int Creature::getMaxHp() const {
    return stats.maxHp;
}

int Creature::getSpeed() const {
    return stats.speed;
}

int Creature::getMaxSpeed() const {
    return stats.maxSpeed;
}

int Creature::getAttack() const {
    return stats.attack;
}

int Creature::getMaxAttack() const {
    return stats.maxAttack;
}

int Creature::getDefense() const {
    return stats.defense;
}

int Creature::getMaxDefense() const {
    return stats.maxDefense;
}

Status Creature::getStatus() const {
    return status;
}

Move* Creature::getMove(int moveKey) const {
    return const_cast<Move *> (&moves[moveKey]);
}

void Creature::setHp(int newHp) {
    stats.hp = newHp;
}

void Creature::setAttack(int newAttack) {
    stats.attack = newAttack;
}

void Creature::setDefence(int newDefence) {
    stats.defense = newDefence;
}

void Creature::setSpeed(int newSpeed) {
    stats.speed = newSpeed;
}