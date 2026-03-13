#ifndef TUI2_H
#define TUI2_H
#include <string>
#include <vector>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define DIM "\033[2m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"


void clearScreen();
void printDivider();
void printHeader(const std::string& title);
void printMenu(const std::vector<std::string>& options);
int readInt(int low, int high);


#endif