#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include "unit.h"
#include "../../common/defines.h"
#include "game.h"


Unit::Unit(YAML::Node& data, int type, std::pair<int, int> pos, int &unitID, int playerID) {
    this->type = type;
    this->cost = data["unidades"][type]["costo"].as<int>();
    this->hp = data["unidades"][type]["vida"].as<int>();
    this->range = data["unidades"][type]["rango"].as<int>();
    this->speed = data["unidades"][type]["velocidad"].as<int>();
    this->trainingTime = data["unidades"][type]["tiempo de entrenamiento"].as<float>();
    this->dimension = std::make_pair(1, 1);
    this->position = pos;
    heading = 0;
    counter = 0;
    this->required = data["unidades"][type]["edificios requeridos"].as<std::vector<int>>();
    if (data["unidades"][type]["casa"])
        this->houses = data["unidades"][type]["casa"].as<std::vector<int>>();
    std::vector<Gun> aux_vec;
    for (size_t i = 0; i < data["unidades"][type]["arma"].size(); i++) {
        std::string gun_name = data["unidades"][type]["arma"][i].as<std::string>();
        Gun aux_gun(data, gun_name);
        aux_vec.push_back(aux_gun);
    }
    this->guns = aux_vec;
    this->id = unitID;
    unitID++;
    this->targetID = -1;
    this->destination = std::make_pair(-1, -1);
    this->playerID = playerID;
    this->nameType = data["unidades"][type]["clase"].as<std::string>();
    isVehicle = this->nameType == "vehiculo";
    this->attacking = false;
}

void Unit::advance(Game& game) {
  Targetable *target = nullptr;
  if (isIdle()) {
    target = game.getTargetInRange(*this);
  } else {
    target = game.getTargetByID(getTargetID());
  }
  attack(target, game);
  move();
}

void Unit::attack(Targetable *target, Game &game) {
    if (!target){
      targetID = -1;
      attacking = false;
      return;
    }
    if (target->getPlayerID() == getPlayerID()){
      targetID = -1;
      attacking = false;
      return;
    }
    if (inRange(target)) {
      stopMoving();
      attacking = true;
      if (canAttack()) {
        target->takeDamage(getDamage(target));
        setLastAttack();
        if (target->getHP() <= 0)
            targetID = -1;
      }
    } else {
      attacking = false;
      moveTo(target->getPosition(), game);
    }
}

bool Unit::inRange(Targetable *target) {
    if (getDistance(target) < CELL_SIZE * range) {
        return true;
    } else {
        return false;
    }
}

float Unit::getAttackRate() {
    float rate = 6 / (float) guns[0].getFrequency();
    return rate;
}

void Unit::setLastAttack() {
    last_attack = std::chrono::steady_clock::now();
}

bool Unit::canAttack() {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    std::chrono::duration<float> seconds = time - last_attack;
    if (seconds.count() > getAttackRate()) {
        return true;
    } else
        return false;
}

void Unit::reset() {
    stopMoving();
    targetID = -1;
    destination = std::make_pair<int, int>(-1, -1);
}

bool Unit::isIdle() {
    if (path.empty() && targetID == -1)
        return true;
    else
        return false;
}

int Unit::getDistance(Targetable *target) {
  int x = abs(target->getPosition().first - position.first);
  int y = abs(target->getPosition().second - position.second);
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}
