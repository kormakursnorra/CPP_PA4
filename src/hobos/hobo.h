#ifndef HOBO_H
#define HOBO_H

#include "zoos/zoo.h"
// #include "items.h"

#include <string>

class Hobo {
public:
    const std::string name;
    static Zoo *zoo;
    // static Items *items;   

    
    void chooseAction();
};

#endif
