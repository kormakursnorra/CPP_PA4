#include "entity.h"
#include <iostream>

Entity::Entity(std::string name, int hp, int attack, int defense, int speed)
    : name(name), hp(hp), maxHp(hp), attack(attack),
    defense(defense), speed(speed), moveCount(0) {}

void Entity::takeDamage(int dmg) {
    int actual = dmg - defense;
    if (actual < 1) actual = 0;
    hp -= actual;
    if (hp < 0) hp = 0;
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
