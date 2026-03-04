#include "battle.h"
#include <iostream>
#include <cstdlib>

Battle::Battle(Entity* player, Entity* opponent)
    : player(player), opponent(opponent) {}

Entity* Battle::whoGoesFirst() {
    return player->getSpeed() >= opponent->getSpeed() ? player : opponent;
}

Entity* Battle::whoGoesSecond() {
    return player->getSpeed() >= opponent->getSpeed() ? opponent : player
    ; 
}

int Battle::calcDmg(Entity* attacker, Move* move) {
    if (!move->hits()) return 0;
    int dmg = (attacker->getAttack() * move->getPower()) / 100;
    return dmg;
}

void Battle::displayStatus() {
    std::cout << "\n";
    player->displayStatus();
    std::cout << " | ";
    opponent->displayStatus();
    std::cout << "\n";
}

void Battle::doTurn(Entity* attacker, Entity* defender) {

    attacker->applyStatusEffect();

    if (attacker->getStatus() == STUNNED) {
        return;
    }

    std::cout << "\n" << attacker->getName() << "'s turn!\n";

    Move* move = attacker->chooseAction();
    int dmg = calcDmg(attacker, move);

    if (dmg == 0) {
        std::cout << attacker->getName() << " used "
            << move->getName() << " but it missed!\n";
    } else {
        defender->takeDamage(dmg);
        std::cout << attacker->getName() << " used " << move->getName()
            << " dealing " << dmg << " damage!\n";
    }
}

void Battle::run() {
    std::cout << "A wild " << opponent->getName() << " appears!\n";

    Entity* first = whoGoesFirst();
    Entity* second = whoGoesSecond();

    while (player->isAlive() && opponent->isAlive()) {
        displayStatus();

        doTurn(first, second);
        if (!second->isAlive()) break;

    doTurn(second, first);
    }

    if (player->isAlive()) {
        std::cout << "\n" << player->getName() << " wins!\n";
    } else {
        std::cout << "\n" << opponent->getName() << " wins!\n";
    }
}
