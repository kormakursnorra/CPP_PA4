#ifndef ITEM_H
#define ITEM_H
#include <string>

class Creature;

enum ItemType {
    HEAL,
    EMPOWER,
    BOLSTER,
    SPEED
};

class Item {
    private:
        const std::string name;
        const std::string description;
        ItemType type;
        int effect;
    
    public:
        Item(const std::string name, 
            const std::string description, 
            ItemType type, int effect
        );

        std::string getItemName() const;
        std::string getItemDescription() const;
        ItemType getItemType() const;
        int getItemEffect() const;
        bool applyItem(Creature* target);

};

#endif