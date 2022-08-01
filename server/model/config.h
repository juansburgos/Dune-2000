#ifndef DUNE_CONFIG_H__
#define DUNE_CONFIG_H__

#include <vector>
#include "building.h"
#include "unit.h"

class Unit;

class Config {
private:
    YAML::Node map;
    YAML::Node assets;
public:
    explicit Config(const std::string &mapName);

    std::vector<std::vector<int>> getTiles();

    std::vector<std::vector<int>> getSpecia();

    std::vector<Building> getBuildings(int &buildingID, int required);

    std::vector<Unit> getUnits(int &unitID);

    YAML::Node& getAssets() { return assets; };

    std::map<int, int> getWormPositions();
};

#endif //DUNE_CONFIG_H__
