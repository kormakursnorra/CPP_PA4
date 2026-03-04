#include "character.h"
#include "entity.h"
#include <iostream>

Character::Character(std::string name, int hp, int attack, int defense, int speed)
    : Entity(name, hp, attack, defense, speed) {}

Move* Character::chooseAction() {
    std::cout << "\nChoose a move:\n";
    displayMoves();

    int choice = 0; 
    while(choice < 1 || choice > moveCount) {
        std::cout << "> ";
        std::cin >> choice;
        std::cin.ignore();
    }

    return &moves[choice - 1];
}
