#ifndef ITEM_H
#define ITEM_H
#include <string>

class Creature;

// enum ItemType {
//     heal,
//     add_attack,
//     add_defence,
//     add_speed
// };

template <typename ItemType>
class Item {
    private:
        const std::string name;
        const std::string description;
        // ItemType type;
        int effect;
    
    public:
        Item(const std::string name, const std::string description, int effect)
        :name(name), description(description), effect(effect) {};

        std::string getItemName() const { return name; };
        std::string getItemDescription() const { return description; };
        // ItemType getItemType() const {return type;} ;
        int getItemEffect() const { return effect; };
        bool applyItem(Creature* target) {
            return static_cast<ItemType*>(this)->applyItem(target);
        };

};

#endif