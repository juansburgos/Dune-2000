#ifndef SERVER_MAPA_H
#define SERVER_MAPA_H

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include "targetable.h"
#include "protocol.h"
#include "config.h"
#include "../../common/defines.h"

class Map {
    std::vector<std::vector<int>> tiles;
    std::vector<std::vector<int>> specia;
    std::vector<std::vector<bool>> used;
    std::vector<int> tileType = TILETYPE_TYPE;
public:
    Map(const std::string &mapName, Config &config);

    std::vector<std::vector<int>> const &getTiles() { return tiles; }

    std::vector<std::vector<int>> const &getSpecia() { return specia; };

    int getSpecia(std::pair<int, int> pos) const { return specia[pos.second][pos.first]; }

    Map(Map &&other) noexcept = default;

    Map(const Map &) = delete;

    Map &operator=(const Map &) = delete;

    void setUsed(Building &building);

    bool positionIsValid(const Building &building, const std::pair<int, int> &position);

    int getH() const { return tiles.size(); }

    int getW() const { return tiles[0].size(); }

    int getTerrain(const std::pair<int, int> &pos) const { return tileType[tiles[pos.second][pos.first]]; }

    bool getUsed(const std::pair<int, int> &pos) const { return used[pos.second][pos.first]; }

    void setUnused(Building &building);

    bool moreSpiceNearby(std::pair<int, int>&pos) const ;

    bool positionIsValid(std::pair<int,int> pos) const;

    void reduceSpiceLevel(std::pair<int, int> pos);
};

#endif //SERVER_MAPA_H
