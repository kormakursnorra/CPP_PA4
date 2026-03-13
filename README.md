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

Gera meira

### Key Classes

### Damage Formula

### Alcohol System

### Building the project

### File Structure