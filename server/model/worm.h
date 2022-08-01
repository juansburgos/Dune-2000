#ifndef WORM__H_
#define WORM__H_

#include <chrono>
#include <map>
#include <vector>
#include "movable.h"
#include "targetable.h"

class Game;

class Worm : public Movable {
    int unitsEaten;
    int searchRange;
    int attackRange;
    int changeInterval;
    float frequency;
    bool attacking;
    std::map<int, int> posiblePositions;
    std::chrono::steady_clock::time_point last_pos_change, last_attack;

    std::pair<int, int> targetPosition;

   public:
    explicit Worm(std::map<int, int> positions);

    bool isIdle();

    void changeLocation(Game &game);

    std::pair<int, int> getRandPosition(Game &game);

    void attack(Targetable *target, Game &game);

    void setLastAttack();

    bool inRange(Targetable *target, int range);

    int getSearchRange() const { return searchRange; }

    bool canAttack();

    float getAttackRate() const;

    int getAttackRange() const { return attackRange; }

    void advance(Game &game);

    bool getAttacking() const { return attacking; }

    std::pair<int, int> getTargetPosition() const { return targetPosition; };
};

#endif
