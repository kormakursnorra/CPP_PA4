#include <iostream>
#include <limits>
#include "tui2.h"
#include "battle_menu.h"
#include "battle.h"

void BattleMenu::_printBattleHeader(const BattleContext& context) const {
    const CreatureInfo& p = context.playerActive;
    const CreatureInfo& e = context.enemyActive;

    std:: cout << BOLD << YELLOW <<"===HOBO FIGHTERS ===\n" << RESET;
    printDivider();
    std::cout << GREEN << p.name << RESET << " HP: " << p.hp << "/" << p.maxHp;
    if (p.status != Status::NONE){
        std::cout << "  Status: " << p.statusName;
    }
    std::cout << " vs " << CYAN << e.name << RESET << " HP: " << e.hp << "/" << e.maxHp;
    if (e.status != Status::NONE){
        std::cout << "  Status: " << e.statusName;
    }
    std::cout << "\n";
    printDivider();
}

int BattleMenu::showBattleMenu(const BattleContext& context) {
    clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    std:: cout << "1. Use Move\n";
    std::cout << "2. Use Item\n";
    std::cout << "3. Drink Booze\n";
    std::cout << "4. Swap Creature\n";
    std::cout << "5. Info\n";
    std::cout << "\n";
    return readInt(1, 5);
}

int BattleMenu::promptMoveMenu(const BattleContext& context) const {

    clearScreen();
    _printBattleHeader(context);
    std:: cout << CYAN << "\n--- Moves ---\n" << RESET;
    const CreatureInfo& c = context.playerActive;

    _printCreatureCard(c);
    std:: cout << "\n";
    int moveCount = (int)c.moves.size();
    
    for (int i = 1; i <= moveCount; i++) {
        const MoveInfo& m = c.moves[i-1];
        std::cout << i << ". " << m.name
                  << "  power: " << m.power;
        if (m.effect != Status::NONE)
            std::cout << "  [" << m.effectChance << "% " << m.effectName << "]";
        std::cout << "\n";
    }

    if (moveCount == 0)
        std::cout << "no moves \n";

    std:: cout << "0. Back \n\n";
    return readInt(0, moveCount);
}

std::string itemTypeName(ItemType type) {
    if (type == HEAL)    return "heal";
    if (type == EMPOWER) return "empower";
    if (type == BOLSTER) return "bolster";
    if (type == SPEED)   return "speed";
    return "unknown";
}

int BattleMenu::promptItemMenu(const BattleContext& context) const {
    clearScreen();
    _printBattleHeader(context);
    std::cout << CYAN << "\n--- Items ---\n"<< RESET;
    int itemCount = (int)context.items.size();

    if (itemCount ==0) {
        std::cout << "No items. \n";
    } else{
        for (int i=1; i<= itemCount; i++){
            const ItemInfo& item = context.items[i-1];
            std::cout << i << ". " << item.name << "  x" << item.quantity << "\n"
                << " Description:" << item.description << "\n" << " Effect: " 
                << item.effect << " Type: " << itemTypeName(item.type) << "\n\n";
        }
    }
    std::cout << "0. Back \n\n";
    return readInt(0, itemCount);
}

int BattleMenu::promptItemCreature(const BattleContext& context) const {
    clearScreen();
    _printBattleHeader(context);
    std::cout << "\n--- Use on which creature? ---\n";
    int aliveCount = 0;

    for (int i = 0; i < (int)context.zoo.size(); ++i) {
        const CreatureInfo& c = context.zoo[i];

        if (!c.alive) continue;
        ++aliveCount;
        std::cout << aliveCount << ".\n";
        _printCreatureCard(c);
        std::cout << "\n";
    }

    std::cout << "0. Back \n\n";
    return readInt(0, aliveCount);
}

int BattleMenu::promptItemConfirm(const BattleContext& context, int creatureIndex, int itemIndex) const {
    const CreatureInfo& target = context.zoo[creatureIndex - 1];
    const ItemInfo& item = context.items[itemIndex - 1];

    clearScreen();
    _printBattleHeader(context);
    std::cout << "\n Use " << item.name << " on " << target.name << "? \n";
    std::cout << "1. Yes \n";
    std::cout << "0. No \n\n";
    return readInt(0, 1);
}

int BattleMenu::promptBoozeMenu(const BattleContext& context) const{
    clearScreen();
    _printBattleHeader(context);
    const BoozeInfo& b =context.booze;
    std::cout <<CYAN<< "\n--- The bottle calls ---\n" <<RESET;
    std::cout << "Booze remaining: " <<b.sipsLeft << "\n";
    std::cout << "Effect pre drink, for all creatures: \n";
    std::cout <<" attack +" << b.attackBoost << " defence +" 
        << b.defenseBoost << " flee chance +" << b. fleeChanceIncrease << "% \n";

    if (b.sipsLeft > 0) {
        std::cout << "1. Bottoms up! \n";
    } else{
        std::cout << " No booze left... \n";
    }
    std::cout << "0. Back \n\n";
    int hi = (b.sipsLeft >0) ? 1:0;
    return readInt(0, hi);

}

int BattleMenu::promptSwapMenu(const BattleContext& contex) const{
    clearScreen();
    _printBattleHeader(contex);
    std::cout << CYAN<<  "\n --- Your zoo ---\n" <<RESET;
    int count=(int) contex.zoo.size();

    for (int i = 1; i <= count; i++){
        const CreatureInfo& c = contex.zoo[i-1];
        std::cout << i << ". ";
        if(!c.alive){
            std::cout << RED<< c.name << " fainted! \n"<<RESET;
        } else {
            if (c.isActive){
                std::cout<< GREEN<< "(active)"<< RESET;
            }
            _printCreatureCard(c);
            std::cout << "\n";
        }   
    }

    std::cout << "0. Back \n\n";
    return readInt(0, count);   
}

void BattleMenu::_printCreatureCard(const CreatureInfo& c) const {
    printDivider();
    std::cout << c.name << " HP: " << c.hp << "/" <<c.maxHp << " Attack: "
        << c.attack << " Defence: " << c.defense << " Speed: " << c.speed;
    if(c.status != Status::NONE){
        std::cout << " Status: " <<c.statusName;
    }
    std::cout<< "\n";
    std::cout << "Moves: ";
    for(int i =0; i< (int)c.moves.size(); ++i){
        if (i>0) std::cout << ", ";
        std::cout << c.moves[i].name;
    }
    std::cout << "\n";
    printDivider();
}

int BattleMenu::promptSwapConfirm(const BattleContext& context, int rosterIndex) const {
    const CreatureInfo& target = context.zoo[rosterIndex - 1];
    clearScreen();
    _printBattleHeader(context);

    if (!target.alive) {
        std::cout << target.name << " has fainted, pick another.\n";
        std::cout << "(press enter) \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    if (target.isActive) {
        std::cout << target.name << " is already out!\n";
        std::cout << "(press enter) \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }

    std::cout << "\n Swap to: \n";
    _printCreatureCard(target);
    std::cout << "1. Yes \n";
    std::cout << "0. No \n\n";
    return readInt(0, 1);
}

void BattleMenu::showInfoMenu() const {
    clearScreen();
    std::cout << BOLD << CYAN
              << "=== HOW TO PLAY ===\n" << RESET;
    printDivider();
    std::cout << "Enter a number and press enter.\n";
    std::cout << "Enter 0 in sub-menu to go back.\n\n";
    std::cout << "Battle options: \n";
    std::cout << "  1. Use Move    - attack with one of your creature's moves \n";
    std::cout << "  2. Use Item    - use something from your stash \n";
    std::cout << "  3. Drink Booze - temporary stat boost, increases flee chance \n";
    std::cout << "  4. Swap        - switch to a different creature \n\n";
    std::cout << "Goal: knock out all of your enemy's creatures.\n";
    printDivider();
    std::cout << "0. Back \n\n";
    readInt(0, 0);
}

void BattleMenu::showTurnResult(const std::string& message) const {
    std::cout << "\n" << message << "\n";
    std::cout << "(press enter to continue)";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void BattleMenu::showBattleOver(const std::string& winnerName) const {
    clearScreen();
    std::cout << BOLD << YELLOW << "=== BATTLE OVER ===\n" << RESET;
    printDivider();
    std::cout << "\n" << winnerName << " wins!\n\n";
}