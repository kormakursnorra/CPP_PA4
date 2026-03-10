#include <iostream>

#include "item.h"
#include "creatures/creature.h"



Item::Item(std::string name, std::string description, ItemType type, int effect)
    :name(name), description(description), type(type), effect(effect) {}

std::string Item::getItemName() const{return name;}
std::string Item::getItemDescription() const{return description;}
ItemType Item::getItemType() const{return type;}
int Item::getItemEffect() const{return effect;}

bool Item::applyItem(Creature* creature) {
    if (type == heal) {
        int hp = creature->getHp();
        int maxHp = creature->getMaxHp();
        int addHp = getItemEffect();
        int newHp = hp + addHp;
        if (hp == maxHp){
            std::cout << creature->getName() << "The HP is full, make another move";
            return false;
        } else if (newHp >= maxHp) {
            creature->setHp(maxHp);
        } else {
            creature->setHp(newHp);
        }
        return true;
    } else if (type == add_attack) {
        int attack = creature->getAttack();
        int maxAttack = creature->getAttack() * 2; //needs fixing
        int addAttack = getItemEffect();
        int newAttack = attack + addAttack;
        if (attack == maxAttack){
            std::cout << creature->getName() << "Attack is at it's capasity, make another move";
            return false;
        } else if (newAttack >= maxAttack) {
            creature->setAttack(maxAttack);
        } else {
            creature->setAttack(newAttack);
        }
        return true;
    } else if (type == add_defence) {
        int defence = creature->getDefense();
        int maxDefence = creature->getDefense() * 2; //needs fixing
        int addDefence = getItemEffect();
        int newDefence = defence + addDefence;
        if (defence == maxDefence){
            std::cout << creature->getName() << "Defence is at it's capasity, make another move";
            return false;
        } else if (newDefence >= maxDefence) {
            creature->setDefence(maxDefence);
        } else {
            creature->setDefence(newDefence);
        }
        return true;
    } else if (type == add_speed) {
        int speed = creature->getSpeed();
        int maxSpeed = creature->getSpeed() * 2; //needs fixing
        int addSpeed = getItemEffect();
        int newSpeed = speed + addSpeed;
        if (speed == maxSpeed){
            std::cout << creature->getName() << "Speed is at it's capasity, make another move";
            return false;
        } else if (newSpeed >= maxSpeed) {
            creature->setSpeed(maxSpeed);
        } else {
            creature->setSpeed(newSpeed);
        }
        return true;
    } else {return false;}

}