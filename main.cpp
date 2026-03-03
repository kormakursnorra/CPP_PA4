#include <iostream>
#include <cstdlib>
#include "Move.h"

int main() {
    Move thunder("Thunderbolt", 90, 100);
    Move tackle("Tackle", 40, 95);

    thunder.display();
    tackle.display();

    std::cout << thunder.getName() << " hits? " << (thunder.hits() ? "yes" : "no") << std::endl;
}
