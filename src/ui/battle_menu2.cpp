#include <iostream>
#include <limits>
#include "tui.h"
#include "battle_menu.h"
#include "battle.h"

void BattleMenu::_printBattleHeader(const BattleContext& context) const {
    const CreatureInfo& p = context.playerActive;
    const CreatureInfo& e = context.enemyActive;

    std:: cout << tui::BOLD << tui::YELLOW <<"===HOBO FIGHTERS ===\n" << tui::RESET;
    tui::printDivider();
    std::cout << tui::GREEN << p.name << tui::RESET << " HP: " << p.hp 
        << "/" << p.maxHp << " vs "
        <<tui:: CYAN << e.name << tui::RESET << " HP: " << e.hp 
        << "/" << e.maxHp << "\n";
    tui::printDivider();
}

int BattleMenu::showBattleMenu(const BattleContext& context) {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    std:: cout << "1. Use Move\n";
    std::cout << "2. Use Item\n";
    std::cout << "3. Drink Booze\n";
    std::cout << "4. Swap Creature\n";
    std::cout << "5. Info\n";
    std::cout << "\n";
    return tui::readInt(1, 5);
}

int BattleMenu::promptMoveMenu(const BattleContext& context) const {

    tui::clearScreen();
    _printBattleHeader(context);
    std:: cout << "\n-- Moves --\n\n";
    const CreatureInfo& c = context.playerActive;

    std::cout << c.name
              << "  HP: " << c.hp << "/" << c.maxHp
              << "  ATK: " << c.attack
              << "  DEF: " << c.defense
              << "  SPD: " << c.speed;

    if (c.status != Status::NONE)
        std::cout << "  [" << c.statusName << "]";
    std:: cout << "\n\n";
    int moveCount = (int)c.moves.size();
    
    for (int i = 0; i < moveCount; ++i) {
        const MoveInfo& m = c.moves[i];
        std::cout << (i + 1) << ". " << m.name
                  << "  pwr: " << m.power;
        if (m.effect != Status::NONE)
            std::cout << "  [" << m.effectChance << "% " << m.effectName << "]";
        std::cout << "\n";
    }

    if (moveCount == 0)
        std::cout << "(no moves)\n";

    std:: cout << "0. Back\n\n";
    return tui::readInt(0, moveCount);
}