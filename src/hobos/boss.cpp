#include "boss.h"
#include <iostream>

Boss::Boss(std::string name, int hp, int attack, int defense, int speed)
    : Enemy(name, hp, attack, defense, speed), enraged(false) {}

Move* Boss::strongestMove() {
    int best = 0;
    for (int i = 1; i < moveCount; i++) {
        if (moves[i].getPower() > moves[best].getPower()) {
            best = i;
        }
    }
    return &moves[best];
}

Move* Boss::chooseAction() {
    // check if boss is mad
    if (!enraged && hp < maxHp / 2) {
        enraged = true;
        std::cout << "\n*** " << getName()
                << " is enraged! ***\n";
    }

    if (enraged) {
        std::cout << getName() << " is overwhelmed with fury!\n";
        return strongestMove();
    }

    return Enemy::chooseAction();
}
