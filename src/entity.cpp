#include "entity.h"
#include <iostream>

Entity::Entity(std::string name, int hp, int attack, int defense, int speed)
    : name(name), hp(hp), maxHp(hp), attack(attack),
    defense(defense), speed(speed), moveCount(0),
    status(NONE), statusDuration(0) {}

void Entity::takeDamage(int dmg) {
    int actual = (int)(((rand() % 5) + dmg) * (100 - defense) / 100);
    if (actual < 1) {
        actual = 1;
    }
    hp -= actual;
    if (hp < 0) {
        hp = 0;
    }
}

bool Entity::isAlive() const {
    return hp > 0;
}

void Entity::displayStatus() const {
    std::cout << name << " (" << hp << "/" << maxHp << ")";
}

void Entity::displayMoves() const {
    for (int i = 0; i < moveCount; i++) {
        std::cout << i + 1 << ". ";
        moves[i].display();
    }
}

void Entity::addMove(Move move) {
    if (moveCount <4) {
        moves[moveCount] = move;
        moveCount++;
    }
}

void Entity::setStatus(Status s, int duration) {
    if (status != NONE) {
        return;
    }
    status = s;
    statusDuration = duration;
    std::cout << name << " is now " << getStatusName() << "!\n";
}

std::string Entity::getStatusName() const {
    switch (status) {
        case INFECTED: return "Infected";
        case STUNNED: return "stunned";
        case BURNED: return "Burned";
        default: return "Fine";
    }

}

void Entity::applyStatusEffect() {
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

std::string Entity::getName() const {
    return name;
}

int Entity::getSpeed() const {
    return speed;
}

int Entity::getAttack() const {
    return attack;
}

int Entity::getDefense() const {
    return defense;
}

Status Entity::getStatus() const {
    return status;
}
