#ifndef ASTAR__H_
#define ASTAR__H_

#include "map.h"
#include "cell.h"
#include <utility>
#include <vector>

typedef std::vector<std::pair<int, int>> Path;

class AStar {
    bool isValid(const Map &map, const std::pair<int, int> &pos);

    bool isUnblocked(const Map &map, const std::pair<int, int> &pos, bool isVehicle, bool isWorm);

    bool isDestination(const std::pair<int, int> &src, const std::pair<int, int> &dest);

    double calculateHValue(const std::pair<int, int> &src, const std::pair<int, int> &dest);

    Path tracePath(const std::vector<std::vector<Cell>> &cellDetails, std::pair<int, int> dest);

    Path find_close_unblocked(Map const &map, std::pair<int, int> &src, std::pair<int, int> &pos, bool isVehicle,
                              bool isWorm);

public:
    Path search(Map const &map, std::pair<int, int> src, std::pair<int, int> dest, bool isVehicle, bool isWorm);
};

#endif
