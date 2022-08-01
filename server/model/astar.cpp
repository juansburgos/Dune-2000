#include "astar.h"
#include <queue>
#include <tuple>
#include <cmath>
#include "defines.h"
#include <iostream>

Path AStar::search(Map const &map, std::pair<int, int> src, std::pair<int, int> dest, bool isVehicle, bool isWorm) {
    std::vector<std::pair<int, int>> path;
    src.first /= CELL_SIZE;
    src.second /= CELL_SIZE;
    dest.first /= CELL_SIZE;
    dest.second /= CELL_SIZE;
    if (!isValid(map, dest)) {
        return path;
    }
    if (!isUnblocked(map, dest, isVehicle, isWorm)) {
        return find_close_unblocked(map, src, dest, isVehicle, isWorm);
    }
    if (isDestination(src, dest)) {
        return path;
    }
    int row = map.getH();
    int col = map.getW();
    std::vector<std::vector<bool>> closedList(row, std::vector<bool>(col));
    for (int i = 0; i < closedList.size(); i++)
        for (int j = 0; j < closedList[0].size(); j++)
            closedList[i][j] = false;
    std::vector<std::vector<Cell>> cellDetails(row, std::vector<Cell>(col));

    int i = src.first;
    int j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = {i, j};

    std::priority_queue<std::tuple<double, int, int>, std::vector<std::tuple<double, int, int>>,
            std::greater<std::tuple<double, int, int>>> openList;

    openList.emplace(0.0, i, j);
    while (!openList.empty()) {
        const std::tuple<double, int, int> &p = openList.top();
        i = std::get<1>(p);
        j = std::get<2>(p);

        openList.pop();
        closedList[i][j] = true;

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
                std::pair<int, int> neighbour(i + add_x, j + add_y);
                if (isValid(map, neighbour)) {
                    if (isDestination(neighbour, dest)) {
                        cellDetails[neighbour.first][neighbour.second].parent = {i, j};
//                        std::cout << "(" << dest.first << "," << dest.second << ") ";
                        path = tracePath(cellDetails, dest);
//                        std::cout << "(" << src.first << "," << src.second << ")" << std::endl;
                        return path;
                    }
                    if (!closedList[neighbour.first][neighbour.second] && isUnblocked(map, neighbour, isVehicle, isWorm)) {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = calculateHValue(neighbour, dest);
                        fNew = gNew + hNew;
                        if (cellDetails[neighbour.first][neighbour.second].f == -1
                            || cellDetails[neighbour.first][neighbour.second].f > fNew) {
                            openList.emplace(fNew, neighbour.first, neighbour.second);
                            cellDetails[neighbour.first][neighbour.second].g = gNew;
                            cellDetails[neighbour.first][neighbour.second].h = hNew;
                            cellDetails[neighbour.first][neighbour.second].f = fNew;
                            cellDetails[neighbour.first][neighbour.second].parent = {i, j};
                        }
                    }
                }
            }
        }
    }
//    std::cout << "Failed to find the destination Cell" << std::endl;
    return path;
}

bool AStar::isValid(const Map &map, const std::pair<int, int> &pos) {
    return (pos.first <= map.getW() && pos.first >= 0 && pos.second <= map.getH() && pos.second >= 0);
}

bool AStar::isUnblocked(const Map &map, const std::pair<int, int> &pos, bool isVehicle, bool isWorm) {
    int terrain = map.getTerrain(pos);
    if (isWorm)
        return terrain == COD_ARENA;
    else {
        if (map.getUsed(pos))
            return false;
        return (!isVehicle && terrain != COD_PRECIPICIO) ||
               (isVehicle && terrain != COD_PRECIPICIO && terrain != COD_CIMA);
    }
}

bool AStar::isDestination(const std::pair<int, int> &src, const std::pair<int, int> &dest) {
    return src == dest;
}

double AStar::calculateHValue(const std::pair<int, int> &src, const std::pair<int, int> &dest) {
    return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
}

Path AStar::tracePath(const std::vector<std::vector<Cell>> &cellDetails, std::pair<int, int> dest) {
//    std::cout << "The path taken was: " << std::endl;
    std::vector<std::pair<int, int>> path;
    int row = dest.first;
    int col = dest.second;
    std::pair<int, int> next_node = dest;
    do {
        std::pair<int, int> aux = next_node;
        aux.first *= CELL_SIZE;
        aux.second *= CELL_SIZE;
        path.push_back(aux);
        next_node = cellDetails[row][col].parent;
        row = next_node.first;
        col = next_node.second;
    } while (cellDetails[row][col].parent != next_node);
//    for (auto cell: path)
//        std::cout << "<- (" << cell.first / CELL_SIZE << "," << cell.second / CELL_SIZE << ") ";
    return path;
}

Path AStar::find_close_unblocked(Map const &map, std::pair<int, int> &src, std::pair<int, int> &pos, bool isVehicle, bool isWorm) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            pos.first += i;
            pos.second += j;
            if (isValid(map, pos) && isUnblocked(map, pos, isVehicle, isWorm)) {
                pos.first *= CELL_SIZE;
                pos.second *= CELL_SIZE;
                src.first *= CELL_SIZE;
                src.second *= CELL_SIZE;
                return search(map, src, pos, isVehicle, isWorm);
            }
        }
    }
    Path path;
    return path;
}
