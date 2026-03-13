#include <iostream>
#include <limits>
#include "tui2.h"

void clearScreen() {
    std::cout << "\033[2J\033[H";
}
void printDivider(){
    std::cout << "----------------------------------------------\n";
}

void printTitle() {
    std::cout << BOLD << RED;
    std::cout << "  _    _  ____  ____   ____    ______ _____ _____ _    _ _______ ______ _____   _____\n";
    std::cout << " | |  | |/ __ \|  _ \ / __ \  |  ____|_   _/ ____| |  | |__   __|  ____|  __ \ / ____|\n";
    std::cout << " | |__| | |  | | |_) | |  | | | |__    | || |  __| |__| |  | |  | |__  | |__) | (___  \n";
    std::cout << " |  __  | |  | |  _ <| |  | | |  __|   | || | |_ |  __  |  | |  |  __| |  _  / \___ \ \n";
    std::cout << " | |  | | |__| | |_) | |__| | | |     _| || |__| | |  | |  | |  | |____| | \ \ ____) |\n";
    std::cout << " |_|  |_|\____/|____/ \____/  |_|    |_____\_____|_|  |_|  |_|  |______|_|  \_\_____/\n";
    std::cout << RESET;
}
int readInt(int low, int high) {
    while (true) {
        std::cout << "> ";
        int value;
        if (std::cin >> value){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= low && value<= high) return value;
        }else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << RED << "Invalid choice, enter a number between " << low << "-" << high << "\n" << RESET;
    }
}

