#include <cstdlib>
#include <ctime>

#include "battle.h"
#include "ui/tui.h"
#include "hobos/player_hobo.h"
#include "hobos/enemy_hobo.h"
#include "hobos/boss.h"
#include "creatures/creature.h"
#include "creatures/move.h"


int main() {
    // srand(time(0));
    srand(time(0));

    // Create player
    PlayerHobo player("Gustavo", "Hernandez Zoo");

    // Player creatures
    Creature* trashPanda = new Creature("Trash Panda", 65, 70, 55, 75);
    trashPanda->addMove(Move("Dumpster Dive", 50, 95, INFECTED, 40, 3));
    trashPanda->addMove(Move("Rabid Bite", 60, 100, POISONED, 20, 4));
    trashPanda->addMove(Move("Trash Toss", 45, 100, NONE, 0, 0));
    trashPanda->addMove(Move("Scavenge", 40, 100, NONE, 0, 0));
    player.addCreature(trashPanda);

    Creature* gutterMutt = new Creature("Gutter Mutt", 75, 80, 60, 70);
    gutterMutt->addMove(Move("Savage Bite", 70, 100, BLEEDING, 30, 3));
    gutterMutt->addMove(Move("Howl", 0, 100, SCARED, 80, 2));
    gutterMutt->addMove(Move("Pack Fury", 65, 95, NONE, 0, 0));
    gutterMutt->addMove(Move("Guard", 0, 100, NONE, 0, 0));
    player.addCreature(gutterMutt);

    Creature* sewerRatKing = new Creature("Sewer Rat King", 10000, 1000, 100, 100);
    sewerRatKing->addMove(Move("Plague Bite", 55, 100, INFECTED, 60, 4));
    sewerRatKing->addMove(Move("Disease Cloud", 40, 90, POISONED, 50, 5));
    sewerRatKing->addMove(Move("Swarm Call", 60, 95, NONE, 0, 0));
    sewerRatKing->addMove(Move("Devine Gnaw", 50, 100, DEVINE, 100, 2));
    player.addCreature(sewerRatKing);

    Creature* alleyCat = new Creature("Alley Cat", 50, 75, 45, 95);
    alleyCat->addMove(Move("Shadow Strike", 65, 100, NONE, 0, 0));
    alleyCat->addMove(Move("Feral Fury", 70, 90, BLEEDING, 25, 2));
    alleyCat->addMove(Move("Claw Slash", 55, 100, NONE, 0, 0));
    alleyCat->addMove(Move("Hiss", 0, 90, SCARED, 40, 2));
    player.addCreature(alleyCat);

    Creature* spriteBottle = new Creature("Sprite Bottle", 40, 85, 35, 80);
    spriteBottle->addMove(Move("Shard Storm", 75, 85, BLEEDING, 70, 3));
    spriteBottle->addMove(Move("Glass Slash", 60, 100, BLEEDING, 40, 2));
    spriteBottle->addMove(Move("Shatter", 80, 80, NONE, 0, 0));
    spriteBottle->addMove(Move("Crystal Cut", 65, 95, NONE, 0, 0));

    Creature* cardboardGolem = new Creature("Cardboard Golem", 90, 60, 85, 40);
    cardboardGolem->addMove(Move("Crushing Weight", 65, 95, WEAKENED, 40, 3));
    cardboardGolem->addMove(Move("Suffocate", 50, 100, STUNNED, 30, 1));
    cardboardGolem->addMove(Move("Paper Cut", 45, 100, BLEEDING, 20, 2));
    cardboardGolem->addMove(Move("Box Slam", 70, 90, NONE, 0, 0));
    player.addCreature(cardboardGolem);

    // Create enemy
    EnemyHobo enemy("Hector", "Los Pollos Hermanos");

    // Enemy creatures
    Creature* subwayLurker = new Creature("Subway Lurker", 70, 75, 65, 65);
    subwayLurker->addMove(Move("Rail Whip", 65, 95, STUNNED, 20, 1));
    subwayLurker->addMove(Move("Darkness Veil", 0, 100, SCARED, 70, 3));
    subwayLurker->addMove(Move("Trackside Slam", 60, 90, NONE, 0, 0));
    subwayLurker->addMove(Move("Tunnel Rush", 60, 95, NONE, 0, 0));
    enemy.addCreature(subwayLurker);

    Creature* dumpsterDemon = new Creature("Dumpster Demon", 80, 70, 70, 50);
    dumpsterDemon->addMove(Move("Rotten Breath", 60, 90, POISONED, 60, 5));
    dumpsterDemon->addMove(Move("Garbage Avalanche", 75, 85, INFECTED, 40, 3));
    dumpsterDemon->addMove(Move("Stench Cloud", 0, 95, WEAKENED, 80, 4));
    dumpsterDemon->addMove(Move("Trash Bash", 65, 100, NONE, 0, 0));
    enemy.addCreature(dumpsterDemon);

    Creature* drainCrawler = new Creature("Drain Crawler", 60, 80, 55, 70);
    drainCrawler->addMove(Move("Toxic Spray", 70, 90, POISONED, 70, 4));
    drainCrawler->addMove(Move("Slime Trail", 45, 100, WEAKENED, 50, 3));
    drainCrawler->addMove(Move("Drain Pull", 65, 95, STUNNED, 25, 1));
    drainCrawler->addMove(Move("Sludge Bomb", 75, 85, NONE, 0, 0));
    enemy.addCreature(drainCrawler);

    Creature* cartSpecter = new Creature("Cart Specter", 55, 75, 50, 85);
    cartSpecter->addMove(Move("Rolling Charge", 70, 95, NONE, 0, 0));
    cartSpecter->addMove(Move("Metal Screech", 0, 100, SCARED, 90, 2));
    cartSpecter->addMove(Move("Cart Crash", 80, 85, STUNNED, 20, 1));
    cartSpecter->addMove(Move("Wheel Spin", 60, 100, NONE, 0, 0));
    enemy.addCreature(cartSpecter);

    Creature* urbanWraith = new Creature("Urban Wraith", 50, 90, 40, 95);
    urbanWraith->addMove(Move("Soul Drain", 75, 90, WEAKENED, 60, 4));
    urbanWraith->addMove(Move("Whisper of Despair", 0, 100, SCARED, 100, 3));
    urbanWraith->addMove(Move("Phantom Strike", 85, 85, NONE, 0, 0));
    urbanWraith->addMove(Move("Haunt", 70, 95, NONE, 0, 0));
    enemy.addCreature(urbanWraith);

    Creature* concreteGargoyle = new Creature("Concrete Gargoyle", 85, 85, 100, 35);
    concreteGargoyle->addMove(Move("Stone Fist", 80, 95, NONE, 0, 0));
    concreteGargoyle->addMove(Move("Rubble Crush", 90, 85, STUNNED, 30, 1));
    concreteGargoyle->addMove(Move("Rock Slide", 75, 90, NONE, 0, 0));
    concreteGargoyle->addMove(Move("Petrify", 0, 80, STUNNED, 60, 2));
    enemy.addCreature(concreteGargoyle);
    
    Battle battle(&player, &enemy);
    battle.run();

    delete trashPanda;
    delete gutterMutt;
    delete sewerRatKing;
    delete alleyCat;
    delete spriteBottle;
    delete cardboardGolem;
    delete subwayLurker;
    delete dumpsterDemon;
    delete drainCrawler;
    delete cartSpecter;
    delete urbanWraith;
    delete concreteGargoyle;
    
    return 0;
}

// Creature* pikachu = new Creature("Pikachu", 60, 55, 40, 90);
// pikachu->addMove(Move("Thunderbolt", 90, 100, STUNNED, 100, 2));
// pikachu->addMove(Move("Quick Attack", 40, 95, NONE, 0 ,0));
// pikachu->addMove(Move("Thunder Wave", 0, 90, BURNED, 100, 2));
// player.addCreature(pikachu);

// Creature* bulbasaur = new Creature("Bulbasaur", 45, 49, 49, 45);
// bulbasaur->addMove(Move("Vine Whip",   45, 100, NONE, 0));
// bulbasaur->addMove(Move("Razor Leaf",  55, 95, NONE, 0));
// bulbasaur->addMove(Move("Leech Seed",  0, 90, INFECTED, 100, 3));
// player.addCreature(bulbasaur);



// Creature* raticate = new Creature("Raticate", 55, 81, 60, 97);
// raticate->addMove(Move("Bite",    60, 100, BURNED, 100, 1));
// raticate->addMove(Move("Scratch", 40, 95, NONE, 0));
// raticate->addMove(Move("Ember",   40, 100, BURNED, 10, 5));
// enemy.addCreature(raticate);

// Creature* geodude = new Creature("Geodude", 40, 80, 100, 20);
// geodude->addMove(Move("Rock Throw", 50, 90, NONE, 0));
// geodude->addMove(Move("Tackle",     35, 95, NONE, 0));
// enemy.addCreature(geodude);

//delete pikachu;
// delete bulbasaur;
// delete raticate;
// delete geodude;