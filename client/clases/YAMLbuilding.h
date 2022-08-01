#ifndef YAMLbuilding__H_
#define YAMLbuilding__H_

#include <utility>

#include "yaml-cpp/yaml.h"

class YAMLbuilding {
   private:
    int type, energy, cost, hp, capacity;
    std::pair<int, int> dimensions;

   public:
    YAMLbuilding(YAML::Node, int type);
    int getType() { return type; }
    int getEnergy() { return energy; }
    int getCost() { return cost; }
    int getHp() { return hp; }
    int getCapacity() { return capacity; }
    std::pair<int, int> getDimensions() { return dimensions; }
};
#endif
