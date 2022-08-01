#ifndef HARVESTER__H_
#define HARVESTER__H_

#include <utility>
#include <chrono>
#include "yaml-cpp/yaml.h"
#include "targetable.h"
#include "movable.h"

class Game;
class Map;

class Harvester : public Targetable, public Movable {
    int spice;
    float trainingTime;
    bool returning = false;
    bool harvesting = false;
    bool unloading = false;
    std::vector<int> required;
    std::vector<int> houses;
    std::pair<int, int> destination, harvest_location;
    std::chrono::steady_clock::time_point harvest_start, unload_start;

public:
    Harvester(YAML::Node& data, std::pair<int, int>pos, int &unitID, int playerID);

    void advance(Game &game);

    Harvester(Harvester &&other) noexcept = default;

    Harvester(const Harvester &) = delete;

    Harvester &operator=(const Harvester &) = delete;

    void setDestination(std::pair<int, int> dest) { destination = dest; }

    bool inRange(Targetable *target);

    void setLastAttack();

    void reset();

    bool isIdle();

    void harvest(Game &gamep);

    int getDistance(Targetable *target);

    std::vector<int> &getRequired() { return required; }

    int &getCost() { return cost; }

    bool isMoving();

    int getTime() { return trainingTime*60; }
};

#endif
