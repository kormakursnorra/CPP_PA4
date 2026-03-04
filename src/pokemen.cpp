#include <iostream>
#include <cstdlib>
#include <ctime>
#include "character.h"
#include "enemy.h"
#include "battle.h"
#include "boss.h"

int main() {
    srand(time(0));
    Character hero("Hreimur", 80, 17, 15, 15);
    hero.addMove(Move("Thunderbolt", 90, 100));
    hero.addMove(Move("Quick Attack", 40, 95));

    Enemy foe("Pidgey", 35, 8, 3, 10);
    foe.addMove(Move("Gust", 40, 100));
    foe.addMove(Move("Tackle", 35, 95));
    
    Boss johnny("Line Up Johnny", 120, 20, 20, 10);
    johnny.addMove(Move("Fade", 80, 100));
    johnny.addMove(Move("Lumma!", 110, 85));
    johnny.addMove(Move("Prump", 40, 100));

    Battle battle(&hero, &johnny);
    battle.run();

    return 0;
}
