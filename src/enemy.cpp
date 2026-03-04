#include "enemy.h"
#include <cstdlib>
#include <iostream>

Enemy::Enemy(std::string name, int hp, int attack, int defense, int speed)
    : Entity(name, hp, attack, defense, speed) {}

Move* Enemy::chooseAction() {
    int choice = rand() % moveCount;
    std::cout << getName() << " is thinking...\n";
    return &moves[choice];
}
