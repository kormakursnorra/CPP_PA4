#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Enemy.h"

int main() {
    srand(time(0));
    Character hero("Pikachu", 50, 12, 5, 15);
    hero.addMove(Move("Thunderbolt", 90, 100));
    hero.addMove(Move("Quick Attack", 40, 95));

    Enemy foe("Pidgey", 35, 8, 3, 10);
    foe.addMove(Move("Gust", 40, 100));
    foe.addMove(Move("Tackle", 35, 95));

    hero.displayStatus();
    std::cout << " | ";
    foe.displayStatus();
    std::cout << "\n";

    Move* chosen = hero.chooseAction();
    std::cout << "You used " << chosen->getName() << "!\n";


    return 0;
}
