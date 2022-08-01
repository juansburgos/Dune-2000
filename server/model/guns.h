#ifndef GUNS__H_
#define GUNS__H_

#include <utility>
#include <map>
#include <string>
#include "targetable.h"
#include "yaml-cpp/yaml.h"

class Gun {
private:
    int damage, frequency;
    bool animation;
    std::map<std::string, int> bonus;

public:
    Gun(YAML::Node &, const std::string &name);

    int getDamage(Targetable *target);

    int &getFrequency() { return frequency; }
};

#endif
