#include "items/booze.h"
#include "items/item.h"
#include <cassert>


Booze::Booze(const std::string name, 
        const std::string description, 
        int effect, ItemType type
    ) 
: Item(name, description, type, effect), maxCapacity(10), sipsLeft(10) {}

int Booze::getSipsLeft() const {
    return sipsLeft;
}

void Booze::takeSip() {
    assert(sipsLeft >= 0);
    sipsLeft--;
}

void Booze::refill() {
    if (sipsLeft + 2 <= maxCapacity ) sipsLeft += 2;
    else sipsLeft = 10;
}