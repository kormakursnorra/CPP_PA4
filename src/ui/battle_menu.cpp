#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "tui.h"
#include "battle_menu.h"
#include "battle.h"  

// Battle Menu (top level)
int BattleMenu::showBattleMenu(const BattleContext &context) {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";

    std::vector<std::string> opts = {
        std::string(tui::FG_GREEN)   + tui::BOLD + "1." + tui::RESET + "  Use Move",
        std::string(tui::FG_YELLOW)  + tui::BOLD + "2." + tui::RESET + "  Use Item",
        std::string(tui::FG_MAGENTA) + tui::BOLD + "3." + tui::RESET + "  Drink Booze",
        std::string(tui::FG_CYAN)    + tui::BOLD + "4." + tui::RESET + "  Swap Creature",
        std::string(tui::FG_WHITE)   + tui::DIM  + "5." + tui::RESET + "  Info / Help",
    };
    tui::printBox(opts, WIDTH, tui::FG_CYAN);

    return tui::readInt(1, 5);
}


// Sub menus 
// 1. Use Move
int BattleMenu::promptMoveMenu(const BattleContext &context) const {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    tui::printHeader("  CHOOSE  A  MOVE  ", WIDTH);
    std::cout << "\n";

    const CreatureInfo &creature = context.playerActive;

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
    // row.str("");
    // row.clear();

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

    return tui::readInt(0, moveCount);
}

// 2. Use Item
int BattleMenu::promptItemMenu(const BattleContext &context) const {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    tui::printHeader("  ITEMS  ", WIDTH);
    std::cout << "\n";

    std::vector<std::string> lines;
    int itemCount = (int)context.items.size();

    if (itemCount == 0) {
        lines.push_back(std::string(tui::FG_YELLOW) + "  (Your pockets are empty pal...)" + tui::RESET);
    } else {
        for (int i = 0; i < itemCount; ++i) {
            const ItemInfo& item = context.items[i];
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

    return tui::readInt(0, itemCount);
}

// int BattleMenu::promptCreatureSelect(const BattleContext &context) const {
//     tui::clearScreen();
//     _printBattleHeader(context);
//     std::cout << "\n";
//     tui::printHeader("  USE ON WHICH CREATURE?  ", WIDTH);
//     std::cout << "\n";

//     std::vector<std::string> targetLines;
//     int aliveCount = 0;
//     std::vector<int> aliveIndices; 

//     for (int i = 0; i < (int)context.zoo.size(); ++i) {
//         const CreatureInfo& creature = context.zoo[i];
//         if (!creature.alive) { continue; }
//         ++aliveCount;
//         aliveIndices.push_back(i);

//         std::ostringstream row;
//         row << tui::FG_YELLOW << tui::BOLD << aliveCount << "." << tui::RESET << "  "
//             << tui::padRight(creature.name, 14)
//             << "  HP: " << tui::hpBar(creature.hp, creature.maxHp, 10);
//         targetLines.push_back(row.str());
//     }

//     targetLines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
//     targetLines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
//     tui::printBox(targetLines, WIDTH, tui::FG_CYAN);

//     return tui::readInt(0, aliveIndices);
// }


// 3. Drink Booze 
int BattleMenu::promptBoozeMenu(const BattleContext &context) const {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    tui::printHeader("  THE  BOTTLE  CALLS  ", WIDTH);
    std::cout << "\n";

    const BoozeInfo& booze = context.booze;

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

    if (booze.sipsLeft > 0) {
        lines.push_back(std::string(tui::FG_GREEN) + tui::BOLD + "1.  BOTTOMS UP!" + tui::RESET);
    }
    else {
        lines.push_back(std::string(tui::FG_RED) + "  No booze left..." + tui::RESET);
    }

    lines.push_back(std::string(tui::DIM) + "─────────────────────" + tui::RESET);
    lines.push_back(std::string(tui::DIM) + "0.  Back"              + tui::RESET);
    tui::printBox(lines, WIDTH, tui::FG_MAGENTA);

    int hi = (booze.sipsLeft > 0) ? 1 : 0;
    return tui::readInt(0, hi);
}


// 4. Swap Creature
int BattleMenu::promptSwapMenu(const BattleContext &context) const {
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";
    tui::printHeader("  ZOO  ROSTER  ", WIDTH);
    std::cout << "\n";

    std::vector<std::string> rosterLines;
    int maxIdx = (int)context.zoo.size();

    for (int i = 0; i < maxIdx; ++i) {
        const CreatureInfo& creature = context.zoo[i];
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
                if (creature.status != Status::NONE)                                                  
                    row << "  " << tui::FG_YELLOW << "[" << creature.statusName << "]" << tui::RESET;
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

    return tui::readInt(0, maxIdx);
}


int BattleMenu::promptSwapConfirm(const BattleContext &context, int rosterIdx) const {
    const CreatureInfo &target = context.zoo[rosterIdx - 1];
    
    tui::clearScreen();
    _printBattleHeader(context);
    std::cout << "\n";

    if (!target.alive) {
        std::cout << tui::FG_RED
                    << "  That creature has been slimed!\n" << tui::RESET
                    << tui::DIM << "  Press Enter to continue..." << tui::RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        tui::readInt(0, 0);
        return 0;
    }

    if (target.isActive) {
        std::cout << tui::FG_YELLOW
                    << "  That creature is already in battle!\n" << tui::RESET
                    << tui::DIM << "  Press Enter to continue..." << tui::RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        tui::readInt(0, 0);
        return 0;
    }

    tui::printBox({
        std::string(tui::FG_WHITE) + "  Swap to "
            + tui::FG_CYAN + tui::BOLD + target.name + tui::RESET + "?",
        "",
        std::string(tui::FG_GREEN) + tui::BOLD + "1.  Yes, send them out!" + tui::RESET,
        std::string(tui::FG_RED)                + "0.  No, go back"        + tui::RESET,
    }, WIDTH, tui::FG_CYAN);

    return tui::readInt(0, 1);
}
        


// 5. Info / Help
void BattleMenu::showInfoMenu() const {
    tui::clearScreen();
    tui::printHeader("  HOBO  FIGHTERS  //  HOW  TO  PLAY  ", WIDTH);
    std::cout << "\n";

     tui::printBox({
        std::string(tui::BOLD) + tui::FG_YELLOW + "  CONTROLS" + tui::RESET,
        "  Enter a number and press Enter to choose.",
        "  Enter 0 in any sub-menu to go back.",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  BATTLE OPTIONS" + tui::RESET,
        std::string(tui::FG_GREEN)   + "  1. Use Move"      + tui::RESET + " - attack with one of your creature's moves.",
        std::string(tui::FG_YELLOW)  + "  2. Use Item"      + tui::RESET + " - use something from your stash.",
        std::string(tui::FG_MAGENTA) + "  3. Drink Booze"   + tui::RESET + " - temporary stat boost, increases flee chance.",
        std::string(tui::FG_CYAN)    + "  4. Swap Creature" + tui::RESET + " - switch to a different creature.",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  HP BAR" + tui::RESET,
        "  " + tui::hpBar(16, 16, 12) + "  Healthy",
        "  " + tui::hpBar(8,  16, 12) + "  Hurting",
        "  " + tui::hpBar(3,  16, 12) + "  Critical!",
        "",
        std::string(tui::BOLD) + tui::FG_YELLOW + "  GOAL" + tui::RESET,
        "  Knock out all of the enemy hobo's creatures.",
        "  Claim the alley. Survive.",
        "",
        std::string(tui::DIM) + "─────────────────────" + tui::RESET,
        std::string(tui::DIM) + "0.  Back" + tui::RESET,
    }, WIDTH, tui::FG_WHITE);

    tui::readInt(0, 0);
}


void BattleMenu::showTurnResult(const std::string &message) const {
    std::cout << "\n" << tui::FG_WHITE << message << tui::RESET << "\n";
    std::cout << tui::DIM << "  Press Enter to continue..." << tui::RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void BattleMenu::showBattleOver(const std::string &winnerName) const {
    tui::clearScreen();
    tui::printHeader("  BATTLE  OVER  ", WIDTH);
    std::cout << "\n";
    tui::printBox({
        std::string(tui::FG_GREEN) + tui::BOLD + "  " + winnerName + " wins!" + tui::RESET,
        "",
        std::string(tui::DIM) + "  The alley is yours." + tui::RESET,
    }, WIDTH, tui::FG_YELLOW);
    std::cout << "\n";
}


// Shared UI helpers
void BattleMenu::_printBattleHeader(const BattleContext &context) const {
    std::cout << tui::BOLD << tui::FG_YELLOW
              << tui::centre("~ HOBO FIGHTERS ~", WIDTH)
              << tui::RESET << "\n";
    tui::printHRule(WIDTH, tui::FG_CYAN);

    // Side-by-side: your active creature vs enemy active creature
    const CreatureInfo& p = context.playerActive;
    const CreatureInfo& e = context.enemyActive;

    std::ostringstream left, right;
    left  << tui::FG_GREEN << tui::BOLD << tui::padRight(p.name, 12) << tui::RESET
          << " " << tui::hpBar(p.hp, p.maxHp, 10);
    if (p.status != Status::NONE) {
        left << " " << tui::FG_YELLOW << "[" << p.statusName << ']' << tui::RESET;
    }
    right << tui::FG_RED   << tui::BOLD << tui::padRight(e.name, 12) << tui::RESET
          << " " << tui::hpBar(e.hp, e.maxHp, 10);
    if (e.status != Status::NONE) {
        right << " " << tui::FG_YELLOW << "[" << e.statusName << ']' << tui::RESET;
    }

    std::cout << "  " << left.str()
              << tui::FG_WHITE << "  vs  " << tui::RESET
              << right.str() << "\n";

    tui::printHRule(WIDTH, tui::FG_CYAN);
}

void BattleMenu::_printCreatureCard(const CreatureInfo& creature) const {
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
    

    if (creature.moveCount == 0) {
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