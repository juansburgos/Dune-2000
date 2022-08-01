#ifndef TARGETABLE__H_
#define TARGETABLE__H_

#include <string>
#include "positonable.h"

class Targetable : virtual public Positionable {
protected:
    int type;
    int id;
    int hp;
    int playerID;
    int cost;
    std::string nameType;
public:
    int &getType() { return type; }

    int &getID() { return id; }

    int &getPlayerID() { return playerID; }

    int &getCost() { return cost; }

    int &getHP() { return hp; }

    void setHP(int newHP) { hp = newHP; }

    void takeDamage(int damage) { hp -= damage; }

    void getEaten() { hp = 0; }

    std::string &getNameType() { return nameType; }
};

#endif
