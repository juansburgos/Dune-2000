#include "worm.h"
#include <time.h>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "astar.h"
#include "defines.h"
#include "game.h"

Worm::Worm(std::map<int, int> positions) : unitsEaten(0), searchRange(6), attackRange(1), changeInterval(30),
                                           frequency(0.5), attacking(false), posiblePositions(std::move(positions)),
                                           last_pos_change(std::chrono::steady_clock::now()),
                                           targetPosition({-192, -192}) {
    position = std::make_pair<int, int>(-192, -192);
    speed = 5;
    isWorm = true;
}

void Worm::changeLocation(Game &game) {
    if (!isIdle())
        return;

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    std::chrono::duration<float> seconds = now - last_pos_change;
    if (seconds.count() > changeInterval) {
        position = getRandPosition(game);
        last_pos_change = std::chrono::steady_clock::now();
    }
}

std::pair<int, int> Worm::getRandPosition(Game &game) {
    std::pair<int, int> randPos, checkPos;
    Map const &map = game.getMap();
    auto it = posiblePositions.begin();
    srand(time(0));
    std::advance(it, rand() % posiblePositions.size());
    randPos.first = it->first;
    randPos.second = it->second;
    checkPos.first = (randPos.first / CELL_SIZE);
    checkPos.second = (randPos.second / CELL_SIZE);
    if (map.getTerrain(checkPos) != COD_ARENA) {
        std::cout << "WRONG WORM POSITION ON MAP FILE" << std::endl;
        return getPosition();
    }
    return randPos;
}

void Worm::attack(Targetable *target, Game &game) {
    if (!target) {
        stopMoving();
        attacking = false;
        return;
    }
    // std::cout << "Worm position: (" << position.first <<" , " << position.second << " )" << std::endl;
    if (inRange(target, attackRange)) {
        targetPosition = target->getPosition();
        attacking = true;
        stopMoving();
        if (canAttack()) {
            target->getEaten();
            setLastAttack();
            unitsEaten++;
            if (unitsEaten >= 4) {
                position = getRandPosition(game);
                last_pos_change = std::chrono::steady_clock::now();
                unitsEaten = 0;
                attacking = false;
            }
        }
    } else {
        attacking = false;
        moveTo(target->getPosition(), game);
    }
}

void Worm::setLastAttack() {
    last_attack = std::chrono::steady_clock::now();
}

bool Worm::inRange(Targetable *target, int range) {
    int x = abs(target->getPosition().first - position.first);
    int y = abs(target->getPosition().second - position.second);
    if (std::sqrt(std::pow(x, 2) + std::pow(y, 2)) <= 32 * range) {
        return true;
    } else {
        return false;
    }
}

bool Worm::canAttack() {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    std::chrono::duration<float> seconds = time - last_attack;
    if (seconds.count() > getAttackRate()) {
        return true;
    } else
        return false;
}

float Worm::getAttackRate() const {
    float rate = 6 / (float) frequency;
    return rate;
}

void Worm::advance(Game &game) {
    Targetable *target = nullptr;
    if (isIdle()) {
        target = game.getTargetInRange(*this);
    }
    attack(target, game);
    move();
    changeLocation(game);
}

bool Worm::isIdle() {
    if (path.empty() && !attacking)
        return true;
    else
        return false;
}
