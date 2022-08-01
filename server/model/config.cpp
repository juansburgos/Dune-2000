#include <fstream>
#include <utility>
#include "defines.h"
#include "config.h"
#include "yaml-cpp/yaml.h"

Config::Config(const std::string &mapname) {
    this->map = YAML::LoadFile("../maps/" + mapname + ".yaml");
    this->assets = YAML::LoadFile("../assets.yaml");
}

std::map<int, int> Config::getWormPositions() {
  std::map<int, int> positions = map["worms"].as<std::map<int, int>>();
  return positions;
}

std::vector<std::vector<int>> Config::getTiles() {
    std::vector<std::vector<int>> tiles;
    for (size_t i = 0; i < map["tiles"].size(); i++) {
        auto aux = map["tiles"][i].as<std::vector<int>>();
        tiles.push_back(aux);
    }
    return tiles;
}

std::vector<std::vector<int>> Config::getSpecia() {
    std::vector<std::vector<int>> specia;
    for (size_t i = 0; i < map["specia"].size(); i++) {
        auto aux = map["specia"][i].as<std::vector<int>>();
        specia.push_back(aux);
    }
    return specia;
}

std::vector<Building> Config::getBuildings(int &buildingID, int required) {
    std::vector<Building> vec;
    for (size_t i = 0; i < required; i++) {
        std::pair<int, int> pos = std::make_pair(map["players"][i][0].as<int>(), map["players"][i][1].as<int>());
        Building aux(assets, TYPE_CENTRO_CONSTRUCCION, pos, buildingID, i);
        vec.push_back(std::move(aux));
    }
    return vec;
}

std::vector<Unit> Config::getUnits(int &unitID) {
    std::vector<Unit> vec;
    for (size_t i = 0; i < map["units"].size(); i++) {
        std::pair<int, int> pos = std::make_pair(map["units"][i][0].as<int>(), map["units"][i][1].as<int>());
        int type = map["units"][i][2].as<int>();
        int playerID = map["units"][i][3].as<int>();
        Unit aux(assets, type, pos, unitID, playerID);
        vec.push_back(std::move(aux));
    }
    return vec;
}
