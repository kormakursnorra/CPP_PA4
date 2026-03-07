#include "ui/tui.h"

#include <iostream>
#include <sstream>
#include <limits>

namespace tui {
    void clearScreen() {
        std::cout << "\033[2J\033[H";
    }

    void printHRule(int width, const char *color) {
        std::cout << color;
        for (int i = 0; i < width; ++i ) {
            std::cout << BOX_H;
        }
        std::cout << RESET << "\n";
    }

    void printHeader(const std::string &title, int width) {
        std::cout << BOLD << FG_YELLOW;
        std::cout << DBOX_TL;
        for (int i = 0; i < width - 2; ++i) { 
            std::cout << DBOX_H; 
        }
        std::cout << DBOX_TR << "\n";

        std::cout << DBOX_V << FG_WHITE;
        int padding = width - 2 - (int)title.size();
        int left  = padding / 2;
        int right = padding - left;
        std::cout << std::string(left, ' ') 
                  << title << std::string(right, ' ');
        std::cout << FG_YELLOW << DBOX_V << "\n";

        std::cout << DBOX_BL;
        for (int i = 0; i < width - 2; ++i) { 
            std::cout << DBOX_H; 
        }
        std::cout << DBOX_BR << RESET << "\n";

    }

    void printBox(const std::vector<std::string> &lines, int width, 
        const char *borderColour) {
            std::cout << borderColour;
            std::cout << BOX_TL;
            for (int i = 0; i < width - 2; ++i) std::cout << BOX_H;
            std::cout << BOX_TR << "\n";


            for (const auto &line : lines) {
                int visible = 0;
                bool inEsc  = false;
                for (unsigned char c : line) {
                    if (c == '\033') { inEsc = true; continue; }
                    
                    if (inEsc && c == 'm') { inEsc = false; continue; }
                    
                    if ((c & 0xC0) == 0x80) { continue; }
                    
                    ++visible;
                }
                int pad = width - 2 - visible;
                if (pad < 0) { pad = 0; }
                std::cout << BOX_V << RESET << " " << line
                          << std::string(pad > 0 ? pad - 1 : 0, ' ')
                          << borderColour << BOX_V << "\n";

            }   

            std::cout << BOX_BL;
            for (int i = 0; i < width - 2; ++i) {
                std::cout << BOX_H;
            }
            std::cout << BOX_BR << RESET << "\n"; 
        }
    
    std::string hpBar(int current, int max, int barWidth) {
        if (max <= 0) { max = 1; }
        float ratio = (float)current / (float)max;
        int filled  = (int)(ratio * barWidth);
        if (filled < 0) { filled = 0; };
        if (filled > barWidth) { filled = barWidth; }

        const char* colour = FG_GREEN;
        if (ratio <= 0.5f) { colour = FG_YELLOW; }
        if (ratio <= 0.25f) { colour = FG_RED; }

        std::ostringstream oss;
        oss << colour;
        for (int i = 0; i < filled; ++i) { 
            oss << BAR_FULL;
        }
        oss << DIM;
        for (int i = filled; i < barWidth; ++i)  { 
            oss << BAR_EMPTY; 
        }
        oss << RESET;
        return oss.str();
    }

    std::string centre(const std::string& text, int width) {
    int len = (int)text.size();
    if (len >= width) { return text; }
    int left  = (width - len) / 2;
    int right = width - len - left;
    return std::string(left, ' ') + text + std::string(right, ' ');
}

    std::string padRight(const std::string& text, int width) {
        int len = (int)text.size();
        if (len >= width) { return text; }
        return text + std::string(width - len, ' ');
    }

    int readInt(int lo, int hi, const std::string& prompt) {
        while (true) {
            std::cout << FG_CYAN << prompt << RESET;
            int val;
            if (std::cin >> val) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (val >= lo && val <= hi) { return val; }
            } else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << FG_RED << "  Invalid choice. Enter " << lo
                    << "-" << hi << ".\n" << RESET;
        }
    }

}