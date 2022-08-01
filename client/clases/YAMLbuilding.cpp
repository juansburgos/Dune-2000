#include "YAMLbuilding.h"

#include <iostream>
YAMLbuilding::YAMLbuilding(YAML::Node data, int type) {
    this->type = type;
    this->energy = data["edificios"][type]["energia"].as<int>();
    this->cost = data["edificios"][type]["costo"].as<int>();
    this->hp = data["edificios"][type]["puntos de estructura"].as<int>();
    this->dimensions = data["edificios"][type]["dimensiones"].as<std::pair<int, int>>();
    if (data["edificios"][type]["capacidad"]) {
        this->capacity = data["edificios"][type]["capacidad"].as<int>();
    } else {
        this->capacity = -1;
    }
}
