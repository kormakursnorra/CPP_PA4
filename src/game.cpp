#include <cstdlib>
#include <ctime>

#include "battle.h"
#include "ui/tui.h"
#include "hobos/player_hobo.h"
#include "hobos/enemy_hobo.h"
#include "creatures/creature.h"
#include "creatures/move.h"


int main() {
    // srand(time(0));
    srand(time(0));

    PlayerHobo player("Hreimur", "HreimurZoo");

    Creature* pikachu = new Creature("Pikachu", 60, 55, 40, 90);
    pikachu->addMove(Move("Thunderbolt", 90, 100, NONE,    0));
    pikachu->addMove(Move("Quick Attack", 40, 95, NONE,    0));
    pikachu->addMove(Move("Thunder Wave", 0,  90, STUNNED, 100));
    player.addCreature(pikachu);

    Creature* bulbasaur = new Creature("Bulbasaur", 45, 49, 49, 45);
    bulbasaur->addMove(Move("Vine Whip",   45, 100, NONE,     0));
    bulbasaur->addMove(Move("Razor Leaf",  55, 95,  NONE,     0));
    bulbasaur->addMove(Move("Leech Seed",  0,  90,  INFECTED, 100));
    player.addCreature(bulbasaur);

    EnemyHobo enemy("Sketchy Dan", "DanZoo");

    Creature* raticate = new Creature("Raticate", 55, 81, 60, 97);
    raticate->addMove(Move("Bite",    60, 100, NONE,   0));
    raticate->addMove(Move("Scratch", 40, 95,  NONE,   0));
    raticate->addMove(Move("Ember",   40, 100, BURNED, 10));
    enemy.addCreature(raticate);

    Creature* geodude = new Creature("Geodude", 40, 80, 100, 20);
    geodude->addMove(Move("Rock Throw", 50, 90, NONE, 0));
    geodude->addMove(Move("Tackle",     35, 95, NONE, 0));
    enemy.addCreature(geodude);

    Battle battle(&player, &enemy);
    battle.run();

    delete pikachu;
    delete bulbasaur;
    delete raticate;
    delete geodude;

    return 0;
}
