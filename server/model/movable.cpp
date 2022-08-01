#include "movable.h"
#include "../../common/defines.h"
#include "astar.h"
#include "game.h"

void Movable::moveTo(std::pair<int, int> destination, Game &game) {
    destination.first = (destination.first / CELL_SIZE) * CELL_SIZE; //redondeo a celda
    destination.second = (destination.second / CELL_SIZE) * CELL_SIZE;
    AStar aStar;
    std::vector<std::pair<int, int>> aPath = aStar.search(game.getMap(), position, destination, isVehicle, isWorm);
    path = aPath;
}

void Movable::move() {
    if (!path.empty()) {
        if (path.back() != position) {
            counter++;
            if (counter * speed > FACTOR_MOVE * TPS_SERVER) {
                counter = 0;
                fine_move();
                if (path.back() == position)
                    path.pop_back();
            }
        }
    }
}

void Movable::fine_move() {
    std::pair<int, int> destination = path.back();
    if (destination.first == position.first) {
        if (destination.second < position.second) {
            //arriba
            position.second -= STEP_MOVE;
            turn(0);
        }
        if (destination.second > position.second) {
            //abajo
            position.second += STEP_MOVE;
            turn(16);
        }
        return;
    }
    if (destination.second == position.second) {
        if (destination.first < position.first) {
            //izquierda
            position.first -= STEP_MOVE;
            turn(24);
        }
        if (destination.first > position.first) {
            //derecha
            position.first += STEP_MOVE;
            turn(8);
        }
        return;
    }
    //Diagonal
    if (position.first < destination.first) {
        // derecha
        position.first += STEP_MOVE;
        if (position.second < destination.second) {
            // abajo
            position.second += STEP_MOVE;
            turn(12);
        } else {
            // arriba
            position.second -= STEP_MOVE;
            turn(4);
        }
    } else {
        // izquierda
        if (position.second < destination.second) {
            // abajo
            position.second += STEP_MOVE;
            turn(20);
        } else {
            // arriba
            position.second -= STEP_MOVE;
            turn(28);
        }
    }
}

void Movable::turn(int to) {
    if (to > heading && (to - heading) < 16) {
        heading++;
        heading %= 32;
    }
    if (to > heading && (to - heading) >= 16) {
        heading += 31;
        heading %= 32;
    }
    if (to < heading && (heading - to) < 16) {
        heading--;
        heading %= 32;
    }
    if (to < heading && (heading - to) >= 16) {
        heading++;
        heading %= 32;
    }
}

void Movable::stopMoving() {
    if (!path.empty())
        path.clear();

}