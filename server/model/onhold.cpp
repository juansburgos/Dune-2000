#include "onhold.h"
#include <chrono>

UnitOnHold::UnitOnHold(Unit &&u, int energyPercentage) : unit(std::move(u)), percentage(0), forRemoval(false),
                                startTime(std::chrono::steady_clock::now()) {
  if (energyPercentage >= 100)
    this->energyPercentage = 100;
  else
    this->energyPercentage = energyPercentage;
}

bool UnitOnHold::isReady() {
  std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
  int seconds = std::chrono::duration_cast<std::chrono::seconds>(time - startTime).count();
  int neededTime = unit.getTime();
  if (energyPercentage < 50)
    neededTime *= 1.6;
  else if (energyPercentage < 80)
    neededTime *= 1.4;
  else if (energyPercentage < 100)
    neededTime *= 1.2;
  neededTime = 5; //SACAR
  percentage = (static_cast<float>(seconds) / static_cast<float>(neededTime))*100;
  if (percentage > 100) {
    forRemoval = true;
    return true;
  }
  return false;
}


HarvesterOnHold::HarvesterOnHold(Harvester &&h, int energyPercentage) : harvester(std::move(h)), percentage(0), forRemoval(false),
                                      startTime(std::chrono::steady_clock::now()) {
if (energyPercentage >= 100)
  this->energyPercentage = 100;
else
  this->energyPercentage = energyPercentage;
}


bool HarvesterOnHold::isReady() {
  std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
  int seconds = std::chrono::duration_cast<std::chrono::seconds>(time - startTime).count();
  int neededTime = harvester.getTime();
  if (energyPercentage < 50)
    neededTime *= 1.6;
  else if (energyPercentage < 80)
    neededTime *= 1.4;
  else if (energyPercentage < 100)
    neededTime *= 1.2;
  neededTime = 15;//SACAR
  percentage = (static_cast<float>(seconds) / static_cast<float>(neededTime))*100;
  if (percentage > 100) {
    forRemoval = true;
    return true;
  }
  return false;
}
