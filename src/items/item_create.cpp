#include "item_create.h"

Item Items::HealthPotion() {
    return Item("Health potion", "Boosts health by ? points", heal, 10);
}

Item Items::AttackPotion() {
    return Item("Attack potion", "Boosts attack by ? points", add_attack, 10);
}

Item Items::DefencePotion() {
    return Item("Defence potion", "Boosts defence by ? points", add_defence, 10);
}

Item Items::SpeedPotion() {
    return Item("Speed potion", "Boosts speed by ? points", add_speed, 10)
}