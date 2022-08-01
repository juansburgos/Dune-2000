#include "map.h"
#include <vector>
#include <iostream>
#include "config.h"
#include "defines.h"

Map::Map(const std::string &mapName, Config &config) : tiles(config.getTiles()), specia(config.getSpecia()){
    used = std::vector<std::vector<bool>>(tiles.size(), std::vector<bool>(tiles[0].size(), false));
}

bool Map::positionIsValid(Building const &building, std::pair<int, int> const &position) {
    for (int y = 0; y < building.getDimension().second; y++) {
        for (int x = 0; x < building.getDimension().first; x++) {
            std::pair<int, int> aux_pos = {position.first / CELL_SIZE + x,
                                           position.second / CELL_SIZE + y};
            if (getTerrain(aux_pos) != COD_ROCA || getUsed(aux_pos))
                return false;
        }
    }
    return true;
}

void Map::setUsed(Building &building) {
    for (int y = 0; y < building.getDimension().second; y++)
        for (int x = 0; x < building.getDimension().first; x++)
            used[building.getPosition().second / CELL_SIZE + y][building.getPosition().first / CELL_SIZE + x] = true;
}

void Map::setUnused(Building &building) {
    for (int y = 0; y < building.getDimension().second; y++)
        for (int x = 0; x < building.getDimension().first; x++)
            used[building.getPosition().second / CELL_SIZE + y][building.getPosition().first / CELL_SIZE + x] = false;
}

bool Map::moreSpiceNearby(std::pair<int, int>&pos) const {
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      std::pair<int, int> auxPos = pos;
      auxPos.first /= CELL_SIZE;
      auxPos.second /= CELL_SIZE;
      auxPos.first += i;
      auxPos.second += j;
      if (positionIsValid(auxPos) && !getUsed(auxPos) && getSpecia(auxPos) > 0) {
        auxPos.first *= CELL_SIZE;
        auxPos.second *= CELL_SIZE;
        pos = auxPos;
        return true;
      }
    }
  }
  return false;
}

bool Map::positionIsValid(std::pair<int,int> pos) const {
  return pos.first >= 0 && pos.first < getW() && pos.second >= 0 && pos.second < getH();
}

void Map::reduceSpiceLevel(std::pair<int,int> pos) {
  specia[pos.second/CELL_SIZE][pos.first/CELL_SIZE] -= 1;
}
