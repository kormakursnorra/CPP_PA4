#ifndef TUI_H
#define TUI_H

#include <string>
#include <vector>


// Terminal graphics: colors and box drawing
namespace tui {

    // Ansi colors
    constexpr const char *RESET = "\033[0m";
    constexpr const char *BOLD  = "\033[1m";
    constexpr const char *DIM   = "\033[2m";

    // Foreground colors
    constexpr const char *FG_RED     = "\033[31m";
    constexpr const char *FG_GREEN   = "\033[32m";
    constexpr const char *FG_YELLOW  = "\033[33m";
    constexpr const char *FG_BLUE    = "\033[34m";
    constexpr const char *FG_MAGENTA = "\033[35m";
    constexpr const char *FG_CYAN    = "\033[36m";
    constexpr const char *FG_WHITE   = "\033[37m";

    // Background colors
    constexpr const char *BG_BLACK   = "\033[40m";
    constexpr const char *BG_RED     = "\033[41m";
    constexpr const char *BG_BLUE    = "\033[44m";
    constexpr const char *BG_MAGENTA = "\033[45m";

    // Characters to draw box 
    constexpr const char *BOX_H  = "─";
    constexpr const char *BOX_V  = "│";
    constexpr const char *BOX_TL = "┌";
    constexpr const char *BOX_TR = "┐";
    constexpr const char *BOX_BL = "└";
    constexpr const char *BOX_BR = "┘";
    constexpr const char *BOX_ML = "├";
    constexpr const char *BOX_MR = "┤";
    constexpr const char *BOX_T  = "┬";
    constexpr const char *BOX_B  = "┴";
    constexpr const char *BOX_X  = "┼";


    constexpr const char *DBOX_H  = "═";
    constexpr const char *DBOX_V  = "║";
    constexpr const char *DBOX_TL = "╔";
    constexpr const char *DBOX_TR = "╗";
    constexpr const char *DBOX_BL = "╚";
    constexpr const char *DBOX_BR = "╝";

    // Block for HP bar
    constexpr const char *BAR_FULL  = "█";
    constexpr const char *BAR_HALF  = "▓";
    constexpr const char *BAR_EMPTY = "░";

    void clearScreen();
    void printHRule(int width, const char *color = tui::FG_CYAN);
    void printHeader(const std::string &title, int width = 60);
    void printBox(const std::vector<std::string> &lines, int width = 60, 
        const char *borderColor = tui::FG_CYAN);

    // Renders a horizontal HP bar
    std::string hpBar(int current, int max, int barWidth = 16);

    // Centre pads text to width chars (no color codes in text)
    std::string centre(const std::string &text, int width);

    // Left pads text to width chars
    std::string padRight(const std::string &text, int width);

    // Read an integer from option range [lo, hi]; returns -1 on "back" / 0 input
    int readInt(int lo, int hi, const std::string &prompt = "> ");
};

#endif