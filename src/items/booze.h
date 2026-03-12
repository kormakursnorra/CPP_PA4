#ifndef BOOZE_H
#define BOOZE_H


#include "items/item.h"


class Booze : public Item {
protected:
    int maxCapacity;
    int sipsLeft;

public: 
    Booze(const std::string name, 
        const std::string description, 
        int effect, ItemType type = EMPOWER);

    int getSipsLeft() const;
    void takeSip();
    void refill();
    
};


#endif