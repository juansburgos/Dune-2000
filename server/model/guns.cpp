#include <map>
#include <string>
#include "guns.h"

Gun::Gun(YAML::Node &data, const std::string &name) {
    this->damage = data["armamento"][name]["daño"].as<int>();
    this->frequency = data["armamento"][name]["frecuencia"].as<int>();
    this->animation = data["armamento"][name]["animacion"].as<bool>();
    if (data["armamento"][name]["bonificacion"])
        this->bonus = data["armamento"][name]["bonificacion"].as<std::map<std::string, int>>();
}

int Gun::getDamage(Targetable *target) {
    if (bonus.size() > 0) {
        std::map<std::string, int>::iterator it = bonus.find(target->getNameType());
        if (it != bonus.end())
            return damage + it->second;
    }
    return damage;
}
