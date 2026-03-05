#include "hobos/player_hobo.h"
#include "hobos/hobo.h"

#include <cstdlib>
#include <iostream>

PlayerHobo::PlayerHobo(const std::string hoboName, std::string zooName) 
: Hobo(hoboName, zooName) {
    
}

int PlayerHobo::nextAction() {
    return 0;
}
