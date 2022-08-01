#ifndef DUNE_CONFIG_H
#define DUNE_CONFIG_H

#include <vector>
#include "buildings.h"
#include "units.h"

class Config {
private:
    YAML::Node assets;
public:
    Config();
};

#endif //DUNE_CONFIG_H
