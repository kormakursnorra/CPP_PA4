#include <iostream>
#include <cstdlib>
#include <ctime>
#include "character.h"
#include "enemy.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "battle.h"
>>>>>>> hreimur
=======
#include "battle.h"
>>>>>>> 180ed7b259e477513e27a24a2c97ecbf4cfe21fa

int main() {
    srand(time(0));
    Character hero("Pikachu", 50, 12, 5, 15);
    hero.addMove(Move("Thunderbolt", 90, 100));
    hero.addMove(Move("Quick Attack", 40, 95));

    Enemy foe("Pidgey", 35, 8, 3, 10);
    foe.addMove(Move("Gust", 40, 100));
    foe.addMove(Move("Tackle", 35, 95));

    Battle battle(&hero, &foe);
    battle.run();

    return 0;
}
