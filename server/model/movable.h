#ifndef DUNE_MOVABLE_H
#define DUNE_MOVABLE_H

#include "positonable.h"
#include <vector>

class Game;

class Movable : virtual public Positionable {
    void turn(int to);

    void fine_move();

protected:
    std::vector<std::pair<int, int>> path;
    bool isVehicle;
    bool isWorm = false; //mejorable con double dispatch
    int speed;
    int counter = 0;
    int heading = 0;

    void stopMoving();

public:
    Movable() = default;

    Movable(Movable &&other) noexcept = default;

    Movable(const Movable &) = delete;

    Movable &operator=(const Movable &) = delete;

    int getHeading() { return heading; }

    void moveTo(std::pair<int, int>, Game &game);

    void move();

};

#endif //DUNE_MOVABLE_H
