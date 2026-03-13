# CPP_PA4
# Hobo Fighter
A turn base battle game, where you control six creatures and battle rival hobos to gain control of the alley!
## For Players
Hobo fighter is a tatical turn based battle game where you command a team of six creatures to defeat rival hobos. Use strategy, items and sometimes booze to emerge victorious.

### How to play

1. *Starting the game*
- Run: `./bin/hobo_fighters`
2. *Controls*
- Use numbers 1-6 to select options/actions
- Press 5 at the home screen to view full controls and instructions
- Navigate menus by selecting numbered options
3. *Battle Actions*
- 1. Attack: Use your creatures move to damage the opponent
- 2. Use Item: use healing items, stat boosters or other consumables
- 3. Drink Booze: Temporarily boost all your creatures attack stats
- 4. Swap Creature: Switch to a different creature from your team
- 5. View Status: Check current stats

### Game Mechanics
**Turn Order**
- Each turn is determined by creatures speed stat (hight = faster)
- Fastest creature attacks first

**Booze System**
- Drinking booze increases your creatures attack power
- Effect stacks with each sip (drink multiple times for bigger buffs)
- However, creatures become less reliable and more prone to fleeing mid battle
- The alcohol wears off each turn, so maintain your buzz strategically!

**How to win?**
- Defet all six of the opponents creatures to win
- When a creature reaches 0 HP you must swap to another creature
- Last standing hobo wins!

### Stats and effects
**Base stats**
- **HP**: How much health your creature has
- **Attack**: Physical damage dealt per hit
- **Defense**: reduces incomming damage
- **Speed**: Determines attack order (higher = faster)

**Status Effects** (can be put on creatures)
- **Stunned**: Skips the effected creatures turn completely
- **Scared**: 30% chance the creature refuses to attack
- **Weakened**: Damage dealt is halved
- **Burned/Poisoned/Infected/Bleeding**: Gradual damage per turn effected

### Wining strat
- Manage your creatures HP carefully with items
- Use booze strategically the attack buff is powerful but creatures become unreliable
- Swap creatures to avoid getting cornered
- Balance offense with defence
---

## For Developers

### Architecture Overview
**Key design patterns used:**
- **Inheritance**: Hobo base class with PlayerHobo and EnemyHobo subclasses
- **Polymorphism**: Creature base class with derived types, virtual methods for battle actions
- **Variant Pattern**: std::variant<UseMove, UseItem, DrinkBooze, SwapCreatures> for type safe actions
- **Template**: Generic Stash<T> container for managing creatures and items
- **Factory/Builder**: BattleContext struct for passing battle state

### Class Hierarchy
Hobo (abstract base)
|--PlayerHobo
|--EnemyHob

Item (base)
|--Booze (special item)

Stash<T> (template container)
|--Zoo (manages creatures)
|--Inventory (manages Items)

### Key Classes
**Hobo**
- Manages a Zoo (creature team) and Inventory (items)
- Tracks alcohol meter for booze effects
- Virtual method NextAction - subclasses decide their turn action
**Creature**
- Base class for all combatants
- Tracks Stats like HP, attack, defense and speed
- Handles status effects and damage calculations
**Move**
- Represents an attack action
- Properties: power, accuracy, effect (status), effect duration, effect chance
**Battle
- Core game loop in run() method
- Manages turn order based on speed
- calcDmg() implements damage formula
- Action dispatch via std::visit() pattern matching
**Items and Booze**
- Item base class for consumables
- Booze extends item with limited sips and refill mechanics
- Items can apply effects: heal, empower (attack boost). etc

### Damage Formula
baseDamage = (attacker.attack * move.power) / 100
Modifiers:
- If weakend status: baseDamage /= 2
- if scared status: 30% chance to deal 0 damage
- Critical hit chance: 10% -> baseDamage *= 2
finalDamage = (baseDamage + variance) * (100 - defender.defense) / 100

### Alcohol System
1. Increment alcoholMeter
2. Decrement booze.sipsLeft
3. Calculate Boost: totalBoost = alcoholMeter * boozePower
4. Apply to all creatures: creature.attack = creature.maxAttack + totalBoost

**Each Turn:**
- player->decayAlcohol() reduces meter by 1
- Creatures attack scales down proportionally
- Flee chance decreases: fleeChance = alcoholMeter * 10%

### Building the project
**Requirements:**
- C++17 compiler (g++ or clang)
- GNU Make
**Build**
```bash
make # Builds executable to bin/hobo_fighters
make clean # Removes build artifacts
make run # Builds and runs the game
```
The makefile compiles all source files with -Wall -Wextra -Werror flags for strict error checking

### Game Flow
1. Init - Game creates player and enemy hobos with their creature teams
2. Main battle loop
   1. Apply status effects from previous turn
   2. Check for defeated creatures auto swap if needed
   3. Get action from both player (player via menu, enemy via AI)
   4. Execute Actions in speed order
   5. Decay alcohol for player
   6. Repeat until one side has no creatures left
3. Victory - Display winner and return to main menu