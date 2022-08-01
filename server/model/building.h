#ifndef BUILDINGS__H_
#define BUILDINGS__H_

#include <utility>
#include "targetable.h"
#include "yaml-cpp/yaml.h"

class Building : public Targetable {
private:
    int energy, capacity;
public:
    Building(YAML::Node& data, int type, std::pair<int, int> pos, int &buildingID, int playerID);
    Building(Building &&other) noexcept = default;
    Building(const Building &) = delete;
    Building &operator=(const Building &) = delete;
    int& getCapacity() { return capacity; }
    int& getEnergy() { return energy; }

};

#endif
