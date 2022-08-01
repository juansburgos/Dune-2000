#ifndef UNITS__H_
#define UNITS__H_

#include <utility>
#include <chrono>
#include "guns.h"
#include "yaml-cpp/yaml.h"
#include "targetable.h"
#include "movable.h"

class Game;

class Map;

class Unit : public Targetable, public Movable {
    int range;
    int targetID;
    float trainingTime;
    bool attacking;
    std::vector<int> required;
    std::vector<int> houses;
    std::vector<Gun> guns;
    std::pair<int, int> destination;
    std::chrono::steady_clock::time_point last_attack;


public:
    Unit(YAML::Node &data, int type, std::pair<int, int> pos, int &unitID, int playerID);

    void advance(Game &game);

    Unit(Unit &&other) noexcept = default;

    Unit(const Unit &) = delete;

    Unit &operator=(const Unit &) = delete; //SE USA PARA VECTOR.ERASE()

    int getTargetID() { return targetID; }

    void attack(Targetable *target, Game &game);

    void setDestination(std::pair<int, int> dest) { destination = dest; }

    bool inRange(Targetable *target);

    int getDamage(Targetable *target) { return guns[0].getDamage(target); }

    void setLastAttack();

    float getAttackRate();

    bool canAttack();

    void reset();

    bool isIdle();

    int getRange() { return range; }

    int getDistance(Targetable *target);

    std::vector<int> &getRequired() { return required; }

    int &getCost() { return cost; }

    void setTargetID(int id) { targetID = id; }

    int getTime() { return trainingTime*60; }

    bool getAttacking() { return attacking; }
};

#endif
