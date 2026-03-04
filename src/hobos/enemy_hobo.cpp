#include "hobos/enemy_hobo.h"

#include <cstdlib>
#include <iostream>

EnemyHobo::EnemyHobo(const std::string name)
    : Hobo(name) {}

Move* EnemyHobo::chooseAction() {
    int choice = rand() % moveCount;
    std::cout << name << " is thinking...\n";
    return &moves[choice];
}
