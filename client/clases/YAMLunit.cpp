#include "YAMLunit.h"

#include <string>
#include <utility>
#include <vector>

YAMLunit::YAMLunit(YAML::Node data, int type) {
    this->type = type;
    this->cost = data["unidades"][type]["costo"].as<int>();
    this->hp = data["unidades"][type]["vida"].as<int>();
    if (data["unidades"][type]["rango"])
        this->range = data["unidades"][type]["rango"].as<int>();
    else
        this->range = -1;
    this->speed = data["unidades"][type]["velocidad"].as<int>();
    this->training_time = data["unidades"][type]["tiempo de entrenamiento"].as<float>();
    this->dimensions = std::make_pair(32, 32);
    this->required = data["unidades"][type]["edificios requeridos"].as<std::vector<int>>();
    if (data["unidades"][type]["casa"])
        this->houses = data["unidades"][type]["casa"].as<std::vector<int>>();
}
