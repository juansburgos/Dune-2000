#include <iostream>
#include <complex>
#include "harvester.h"
#include "game.h"

Harvester::Harvester(YAML::Node& data, std::pair<int, int>pos, int &unitID, int playerID) {
    this->cost = data["cosechadora"]["costo"].as<int>();
    this->hp = data["cosechadora"]["vida"].as<int>();
    this->speed = data["cosechadora"]["velocidad"].as<int>();
    this->trainingTime = data["cosechadora"]["tiempo de entrenamiento"].as<float>();
    this->dimension = std::make_pair(1, 1);
    this->position = pos;
    this->required = data["cosechadora"]["edificios requeridos"].as<std::vector<int>>();
    this->id = unitID;
    unitID++;
    this->destination = std::make_pair(-1, -1);
    this->playerID = playerID;
    this->spice = 0;
    this->nameType = data["cosechadora"]["clase"].as<std::string>();
    isVehicle = this->nameType == "vehiculo";
}

void Harvester::advance(Game& game) {
  harvest(game);
  move();
}

void Harvester::harvest(Game& game) {
  if (spice == 200 && !returning) { // cambiar numero a 200
    Targetable* refinery = game.getClosestRefinery(*this);
    if (refinery) {
      moveTo(refinery->getPosition(), game);
      returning = true;
    }
  } else if (!isMoving() && returning) {
    if (!unloading) {
      unload_start = std::chrono::steady_clock::now();
      unloading = true;
    } else if (spice > 0) {
      std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
      int milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time - unload_start).count();
      if (milliseconds > 250) {
        game.addMoney(10, getPlayerID());
        spice -= 10;
        unload_start = time;
      }
    } else {
      unloading = false;
      returning = false;
      if (harvesting){
        moveTo(harvest_location, game);
      }
    }
  } else if (!isMoving()) {
    Map const &map = game.getMap();
    std::pair<int, int> auxPos = getPosition();
    auxPos.first /= CELL_SIZE;
    auxPos.second /= CELL_SIZE;
    int spiceLevel = map.getSpecia(auxPos);
    if (!harvesting && spiceLevel > 0 && spice < 200) {
      harvest_start = std::chrono::steady_clock::now();
      harvesting = true;
      harvest_location = getPosition();
    } else if (harvesting && spiceLevel > 0) {
      std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
      int seconds = std::chrono::duration_cast<std::chrono::seconds>(time - harvest_start).count();
      if (seconds > 5) {
        spice += 50;
        game.reduceSpiceLevel(getPosition());
        harvest_start = time;
      }
    } else if (harvesting && map.moreSpiceNearby(harvest_location)) {
      moveTo(harvest_location, game);
    } else if (harvesting) {
      Targetable* refinery = game.getClosestRefinery(*this);
      if (refinery) {
        moveTo(refinery->getPosition(), game);
        returning = true;
        harvesting = false;
        // harvest_location = refinery->getPosition();
      }
    }
  }
}

bool Harvester::isIdle() {
    return path.empty() && !harvesting;
}

bool Harvester::isMoving() {
  return !path.empty();
}

int Harvester::getDistance(Targetable *target) {
  int x = abs(target->getPosition().first - position.first);
  int y = abs(target->getPosition().second - position.second);
  return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

void Harvester::reset() {
  stopMoving();
  returning = false;
  harvesting = false;
}
