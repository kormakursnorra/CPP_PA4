#include "ui/display_menu.h"
#include "ui/tui.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>


DisplayMenu::DisplayMenu(const MenuContext& context) 
: _context(context) {}


// Pre battle
int DisplayMenu::showPreBattle() {
    tui::clearScreen();
    tui::printHeader("~ HOBO FIGHTERS ~", WIDTH);
    std::cout << "\n";

    std::cout << tui::FG_RED << tui::BOLD
              << "  A wild " << _context.enemyName
              << " blocks your shopping cart!\n"
              << tui::RESET << "\n";

    _printCreatureCard(_context.active);
    std::cout << "\n";

    tui::printBox({
        std::string(tui::FG_GREEN)  + tui::BOLD + "1." + tui::RESET + "  Fight Enemy",
        std::string(tui::FG_YELLOW) + tui::BOLD + "2." + tui::RESET + "  Run Away  "
            + tui::DIM + "(coward)" + tui::RESET,
    }, WIDTH, tui::FG_CYAN);

    return tui::readInt(1, 2);
}

// Battle Menu (top level)
int DisplayMenu::showBattleMenu() {
    while (true) {
        tui::clearScreen();
        _printBattleHeader();
        std::cout << "\n";

        std::vector<std::string> opts = {
            std::string(tui::FG_GREEN)   + tui::BOLD + "1." + tui::RESET + "  Use Move",
            std::string(tui::FG_YELLOW)  + tui::BOLD + "2." + tui::RESET + "  Use Item",
            std::string(tui::FG_MAGENTA) + tui::BOLD + "3." + tui::RESET + "  Drink Booze",
            std::string(tui::FG_CYAN)    + tui::BOLD + "4." + tui::RESET + "  Swap Creature",
            std::string(tui::FG_WHITE)   + tui::DIM  + "5." + tui::RESET + "  Info / Help",
        };
        tui::printBox(opts, WIDTH, tui::FG_CYAN);

        int choice = tui::readInt(1, 5);

        switch (choice) {
            case 1: { int ret = _showMoveMenu(); if (ret != 0) { return 1; break; } }
            case 2: { int ret = _showItemMenu(); if (ret != 0) { return 2; break; } }
            case 3: { int ret = _showBoozeMenu(); if (ret != 0) { return 3; break; } }
            case 4: { int ret = _showSwapMenu(); if (ret != 0) { return 4; break; } }
            case 5: { _showInfoMenu(); break; }
        }
    }
}

// Sub menus 
// 1. Use Move
int DisplayMenu::_showMoveMenu() {
    tui::clearScreen();
    _printBattleHeader();
    std::cout << "\n";
    tui::printHeader("  CHOOSE  A  MOVE  ", WIDTH);
    std::cout << "\n";

    const CreatureInfo &creature = _context.active;

    // Creature info summary
    std::ostringstream row;
    row << tui::FG_WHITE << tui::BOLD << tui::padRight(creature.name, 16) << tui::RESET
        << "  HP: " << tui::hpBar(creature.hp, creature.maxHp, 14)
        << "  ATK " << tui::FG_RED   << creature.attack  << tui::RESET
        << "  DEF " << tui::FG_BLUE  << creature.defense << tui::RESET
        << "  SPD " << tui::FG_CYAN  << creature.speed   << tui::RESET;
    
    std::vector<std::string> info = { row.str() };
    if (creature.status != Status::NONE) {
        info.push_back(std::string(tui::FG_YELLOW) + "  Status: " + creature.statusName + tui::RESET);
    }
    tui::printBox(info, WIDTH, tui::FG_MAGENTA);
    std::cout << "\n";
    row.str("");
    row.clear();

    // Move list
    std::vector<std::string> moveLines;
    int moveCount = (int)creature.moves.size();

    for (int i = 0; i < moveCount; ++i) {
        const MoveInfo& move = creature.moves[i];
        std::ostringstream row;
        
        row << tui::FG_YELLOW << tui::BOLD << (i + 1) << "." << tui::RESET << "  "
            << tui::padRight(move.name, 18)
            << "  PWR " << tui::FG_RED << std::setw(3) << move.power
            << "  ACC " << tui::FG_BLUE << tui::RESET;
        
        if (move.effect != Status::NONE) {
            row << "  " << tui::FG_MAGENTA
                << "[" << move.effectChance << "% effect]" << tui::RESET;
        }
        moveLines.push_back(row.str());
    }

    if (moveCount == 0) {
        moveLines.push_back(std::string(tui::FG_RED) + "  No moves available!" + tui::RESET);
    }

    moveLines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
    moveLines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
    tui::printBox(moveLines, WIDTH, tui::FG_YELLOW);

    int choice = tui::readInt(0, moveCount);
    _lastMoveChoice = choice;
    return choice;
}

// 2. Use Item
int DisplayMenu::_showItemMenu() {
    tui::clearScreen();
    _printBattleHeader();
    std::cout << "\n";
    tui::printHeader("  ITEMS  ", WIDTH);
    std::cout << "\n";

    std::vector<std::string> lines;
    int itemCount = (int)_context.items.size();

    if (itemCount == 0) {
        lines.push_back(std::string(tui::FG_YELLOW) + "  (Your pockets are empty pal...)" + tui::RESET);
    } else {
        for (int i = 0; i < itemCount; ++i) {
            const ItemInfo& item = _context.items[i];
            std::ostringstream row;
            row << tui::FG_YELLOW << tui::BOLD << (i + 1) << "." << tui::RESET << "  "
                << tui::padRight(item.name, 20)
                << "  x" << item.quantity;
            lines.push_back(row.str());
        }
    }
    
    lines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
    lines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
    tui::printBox(lines, WIDTH, tui::FG_YELLOW);

    int itemChoice = tui::readInt(0, itemCount);
    if (itemChoice == 0) { return 0; }
    _lastItemChoice = itemChoice;

    tui::clearScreen();
    _printBattleHeader();
    std::cout << "\n";
    tui::printHeader("  USE ON WHICH CREATURE?  ", WIDTH);
    std::cout << "\n";

    std::vector<std::string> targetLines;
    int aliveCount = 0;
    std::vector<int> aliveIndices; 

    for (int i = 0; i < (int)_context.zoo.size(); ++i) {
        const CreatureInfo& creature = _context.zoo[i];
        if (!creature.alive) { continue; }
        ++aliveCount;
        aliveIndices.push_back(i);

        std::ostringstream row;
        row << tui::FG_YELLOW << tui::BOLD << aliveCount << "." << tui::RESET << "  "
            << tui::padRight(creature.name, 14)
            << "  HP: " << tui::hpBar(creature.hp, creature.maxHp, 10);
        targetLines.push_back(row.str());
    }

    targetLines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
    targetLines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
    tui::printBox(targetLines, WIDTH, tui::FG_CYAN);

    int targetChoice = tui::readInt(0, aliveCount);
    if (targetChoice == 0) { return 0; }

    // Return the 1-based roster index of the chosen creature
    _lastItemTarget = aliveIndices[targetChoice - 1] + 1;
    return 1;
}


// 3. Drink Booze 
int DisplayMenu::_showBoozeMenu() {
    tui::clearScreen();
    _printBattleHeader();
    std::cout << "\n";
    tui::printHeader("  THE  BOTTLE  CALLS  ", WIDTH);
    std::cout << "\n";

    const BoozeInfo& booze = _context.booze;

    std::vector<std::string> lines;
    
    std::ostringstream row;
    row << tui::FG_MAGENTA << tui::BOLD
        << "  Booze remaining: " << booze.sipsLeft << tui::RESET;
    lines.push_back(row.str());
    row.str("");
    row.clear();

    lines.push_back("");
    lines.push_back(std::string(tui::BOLD) + tui::FG_WHITE + "  Effects per drink:" + tui::RESET);
    
    row << "    All creatures:"
        << "  ATK +" << tui::FG_RED  << booze.attackBoost  << tui::RESET
        << "  DEF +" << tui::FG_BLUE << booze.defenseBoost << tui::RESET;
    lines.push_back(row.str());
    row.str("");
    row.clear();
    
    row << "    " << tui::FG_YELLOW
        << "Flee chance +" << booze.fleeChanceIncrease << "%" << tui::RESET
        << " per creature";
    lines.push_back(row.str());
    row.str("");
    row.clear();

    lines.push_back("");

    if (booze.sipsLeft > 0)
        lines.push_back(std::string(tui::FG_GREEN) + tui::BOLD + "1.  BOTTOMS UP!" + tui::RESET);
    else
        lines.push_back(std::string(tui::FG_RED) + "  No booze left..." + tui::RESET);

    lines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
    lines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
    tui::printBox(lines, WIDTH, tui::FG_MAGENTA);

    return tui::readInt(0, booze.sipsLeft > 0 ? 1 : 0);
}


// 4. Swap Creature
int DisplayMenu::_showSwapMenu() {
    while (true) {
        tui::clearScreen();
        _printBattleHeader();
        std::cout << "\n";
        tui::printHeader("  ZOO  ROSTER  ", WIDTH);
        std::cout << "\n";

        std::vector<std::string> rosterLines;
        int maxIdx = (int)_context.zoo.size();

        for (int i = 0; i < maxIdx; ++i) {
            const CreatureInfo& creature = _context.zoo[i];
            std::ostringstream row;

            if (creature.isActive)
                row << tui::FG_GREEN << tui::BOLD;
            else
                row << tui::FG_YELLOW << tui::BOLD;

            row << (i + 1) << "." << tui::RESET << "  "
                << tui::padRight(creature.name, 14);

            if (!creature.alive) {
                row << tui::FG_RED << "  [FAINTED]" << tui::RESET;
            } else {
                row << "  HP: " << tui::hpBar(creature.hp, creature.maxHp, 10)
                    << "  ATK " << tui::FG_RED  << creature.attack  << tui::RESET
                    << "  DEF " << tui::FG_BLUE << creature.defense << tui::RESET
                    << "  SPD " << tui::FG_CYAN << creature.speed   << tui::RESET;
            }

            if (creature.isActive)
                row << tui::FG_GREEN << "  < active" << tui::RESET;

            rosterLines.push_back(row.str());

            // Moves sub-line
            std::string moveStr = "     Moves: ";
            for (int moveIdx = 0; moveIdx < (int)creature.moves.size(); ++moveIdx) {
                if (moveIdx > 0) moveStr += ", ";
                moveStr += creature.moves[moveIdx].name;
            }
            rosterLines.push_back(std::string(tui::DIM) + moveStr + tui::RESET);
            rosterLines.push_back("");
        }
        rosterLines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
        rosterLines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
        tui::printBox(rosterLines, WIDTH, tui::FG_CYAN);

        int choice = tui::readInt(0, maxIdx);
        if (choice == 0) { return 0; }

        const CreatureInfo& target = _context.zoo[choice - 1];

        if (!target.alive) {
            std::cout << tui::FG_RED
                      << "  That creature has fainted!\n" << tui::RESET
                      << tui::DIM << "  Press Enter to continue..." << tui::RESET;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (target.isActive) {
            std::cout << tui::FG_YELLOW
                      << "  That creature is already in battle!\n" << tui::RESET
                      << tui::DIM << "  Press Enter to continue..." << tui::RESET;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Confirm sub-menu
        tui::clearScreen();
        _printBattleHeader();
        std::cout << "\n";

        tui::printBox({
            std::string(tui::FG_WHITE) + "  Swap to "
                + tui::FG_CYAN + tui::BOLD + target.name + tui::RESET + "?",
            "",
            std::string(tui::FG_GREEN) + tui::BOLD + "1.  Yes, send them out!" + tui::RESET,
            std::string(tui::FG_RED)                + "2.  No, go back"        + tui::RESET,
        }, WIDTH, tui::FG_CYAN);

        if (tui::readInt(1, 2) == 1) {
            _lastSwapTarget = choice; // 1-based roster index
            return 1;
        }
    }
}
        


// 5. Info / Help
void DisplayMenu::_showInfoMenu() {
    tui::clearScreen();
    tui::printHeader("  HOBO  FIGHTERS  //  HOW  TO  PLAY  ", WIDTH);
    std::cout << "\n";

    tui::printBox({
        std::string(tui::BOLD) + tui::FG_YELLOW + "  CONTROLS"                              + tui::RESET,
        "  Enter a number and press Enter to choose.",
        "  Enter 0 in any sub-menu to go back.",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  BATTLE OPTIONS"                        + tui::RESET,
        std::string(tui::FG_GREEN)   + "  1. Use Move"      + tui::RESET + " - attack with one of your creature's moves.",
        std::string(tui::FG_YELLOW)  + "  2. Use Item"      + tui::RESET + " - use something from your stash.",
        std::string(tui::FG_MAGENTA) + "  3. Drink Booze"   + tui::RESET + " - temporary stat boost, increases flee chance.",
        std::string(tui::FG_CYAN)    + "  4. Swap Creature" + tui::RESET + " - switch to a different creature.",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  HP BAR"                                + tui::RESET,
        "  " + tui::hpBar(16, 16, 12) + "  Healthy",
        "  " + tui::hpBar(8,  16, 12) + "  Hurting",
        "  " + tui::hpBar(3,  16, 12) + "  Critical!",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  GOAL"                                  + tui::RESET,
        "  Knock out all of the enemy hobo's creatures.",
        "  Claim the alley. Survive.",
        "",
        std::string(tui::DIM) + "─────────────────────"                                     + tui::RESET,
        std::string(tui::DIM) + "0.  Back"                                                   + tui::RESET,
    }, WIDTH, tui::FG_WHITE);

    tui::readInt(0, 0);
}


// Shared UI helpers
void DisplayMenu::_printBattleHeader() const {
    std::cout << tui::BOLD << tui::FG_YELLOW
              << tui::centre("~ HOBO FIGHTERS ~", WIDTH)
              << tui::RESET << "\n";
    tui::printHRule(WIDTH, tui::FG_CYAN);

    // Side-by-side: your active creature vs enemy active creature
    const CreatureInfo& p = _context.active;
    const CreatureInfo& e = _context.enemyActive;

    std::ostringstream left, right;
    left  << tui::FG_GREEN << tui::BOLD << tui::padRight(p.name, 12) << tui::RESET
          << " " << tui::hpBar(p.hp, p.maxHp, 10);
    right << tui::FG_RED   << tui::BOLD << tui::padRight(e.name, 12) << tui::RESET
          << " " << tui::hpBar(e.hp, e.maxHp, 10);

    std::cout << "  " << left.str()
              << tui::FG_WHITE << "  vs  " << tui::RESET
              << right.str() << "\n";

    tui::printHRule(WIDTH, tui::FG_CYAN);
}

void DisplayMenu::_printCreatureCard(const CreatureInfo& creature) const {
    std::vector<std::string> lines;

    std::ostringstream row;
    row << tui::FG_GREEN << tui::BOLD << creature.name << tui::RESET;
    if (creature.status != Status::NONE)
        row << "  " << tui::FG_YELLOW << "[" << creature.statusName << "]" << tui::RESET;
    lines.push_back(row.str());
    row.str("");
    row.clear();

    row << "HP: " << tui::hpBar(creature.hp, creature.maxHp, 14)
        << "  " << creature.hp << "/" << creature.maxHp;
    lines.push_back(row.str());
    row.str("");
    row.clear();

    row << "ATK " << tui::FG_RED  << creature.attack  << tui::RESET
        << "  DEF " << tui::FG_BLUE << creature.defense << tui::RESET
        << "  SPD " << tui::FG_CYAN << creature.speed   << tui::RESET;
        lines.push_back(row.str());
    row.str("");
    row.clear();
    

    if (!creature.moves.empty()) {
        lines.push_back(std::string(tui::DIM) + "Moves:" + tui::RESET);
        for (int i = 0; i < (int)creature.moves.size(); ++i) {
            const MoveInfo& move = creature.moves[i];
            std::ostringstream row;
            row << "  " << tui::FG_YELLOW << (i + 1) << "." << tui::RESET << " "
                << tui::padRight(move.name, 16)
                << " PWR " << tui::FG_RED << move.power << tui::RESET;
            lines.push_back(row.str());
        }
    }

    tui::printBox(lines, WIDTH, tui::FG_GREEN);
}