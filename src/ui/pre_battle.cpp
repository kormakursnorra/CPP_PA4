int showPreBattle() {
    tui::clearScreen();
    tui::printHeader("~ HOBO FIGHTERS ~", WIDTH);
    std::cout << "\n";

    std::cout << tui::FG_RED << tui::BOLD
              << "  A wild " << _context.enemyName
              << " blocks your shopping cart!\n"
              << tui::RESET << "\n";

    _printCreatureCard(_context.enemyActive);
    std::cout << "\n";

    tui::printBox({
        std::string(tui::FG_GREEN)  + tui::BOLD + "1." + tui::RESET + "  Fight Enemy",
        std::string(tui::FG_YELLOW) + tui::BOLD + "2." + tui::RESET + "  Run Away  "
            + tui::DIM + "(coward)" + tui::RESET,
    }, WIDTH, tui::FG_CYAN);

    return tui::readInt(1, 2);
}