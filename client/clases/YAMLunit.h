#ifndef YAMLunit__H_
#define YAMLunit__H_

#include <utility>

#include "yaml-cpp/yaml.h"

class YAMLunit {
   private:
    int type, cost, hp, range, speed;
    float training_time;
    std::pair<int, int> dimensions;
    std::vector<int> houses;
    std::vector<int> required;

   public:
    YAMLunit(YAML::Node, int type);
    int getType() { return type; }
    std::pair<int, int> getDimensions() { return dimensions; }
    std::vector<int> getRequired() { return required; }
    int getHp() { return hp; }
    int getCost() { return cost; }
};

#endif
