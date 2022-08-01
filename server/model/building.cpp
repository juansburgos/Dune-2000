#include <utility>
#include "building.h"

Building::Building(YAML::Node& data, int type, std::pair<int, int> pos, int &buildingID, int playerID) {
  this->type = type;
  this->energy = data["edificios"][type]["energia"].as<int>();
  this->cost = data["edificios"][type]["costo"].as<int>();
  this->hp = data["edificios"][type]["puntos de estructura"].as<int>();
  this->dimension = data["edificios"][type]["dimensiones"].as<std::pair<int, int>>();
  this->position = pos;
  if(data["edificios"][type]["capacidad"]){
    this->capacity = data["edificios"][type]["capacidad"].as<int>();
  } else {
    this->capacity = 0;
  }
  this->id = buildingID;
  buildingID++;
  this->playerID = playerID;
  this->nameType = "edificios";
}
