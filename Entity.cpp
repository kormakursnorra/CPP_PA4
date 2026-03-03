#include "Entity.h"
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
