#ifndef INCREATION__H_
#define INCREATION__H_

#include <utility>
#include <chrono>
#include "harvester.h"
#include "unit.h"

class UnitOnHold { //Esto podría haber sido un template
public:
  Unit unit;
  int percentage, energyPercentage;
  bool forRemoval;
  std::chrono::steady_clock::time_point startTime;
  bool isReady();
  bool isForRemoval() { return forRemoval; }
  UnitOnHold(Unit &&u, int energyPercentage);
  UnitOnHold(UnitOnHold&&) = default;
  Unit& getUnit() {  return unit; }
  int getType() { return unit.getType(); }
  int getPlayerID() { return unit.getPlayerID(); }
  int getPercentage() { return percentage; }
};

class HarvesterOnHold {
public:
  Harvester harvester;
  int percentage, energyPercentage;
  bool forRemoval;
  std::chrono::steady_clock::time_point startTime;
  bool isReady();
  bool isForRemoval() { return forRemoval; }
  HarvesterOnHold(Harvester &&h, int energyPercentage);
  HarvesterOnHold(HarvesterOnHold&&) = default;
  Harvester& getHarvester() {  return harvester; }
  int getPlayerID() { return harvester.getPlayerID(); }
  int getPercentage() { return percentage; }

};

#endif
