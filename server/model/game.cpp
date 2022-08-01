#include "game.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "../smsgconstruir.h"
#include "../smsgcrearunidad.h"
#include "../smsgdestruir.h"
#include "../smsgmover.h"
#include "defines.h"
#include "onhold.h"
#include "protocol.h"

Game::Game(std::string name, const std::string &mapName, int required, int house) : name(std::move(name)),
                                                                                           required(required),
                                                                                           config(mapName),
                                                                                           map(mapName, config),
                                                                                           worm(config.getWormPositions()) {
    unirse(house);
    buildings = config.getBuildings(uniqueID, required);
    for (auto &building : buildings) {
        map.setUsed(building);
    }
}

bool Game::unirse(int &house) {
    if (players < required) {
        playerInfo.push_back(PlayerInfo(house, players));
        players++;
        return true;
    }
    return false;
}

bool Game::checkStarting() {
    if ((players == required) && (!started)) {
        std::string str = "Comenzando partida " + name + "...\n";
        std::cout << str;
        started = true;
        return true;
    }
    return false;
}

std::vector<std::vector<int>> const &Game::getTiles() {
    return map.getTiles();
}

std::vector<std::vector<int>> const &Game::getSpecia() {
    return map.getSpecia();
}

std::vector<StBuilding> Game::getBuildings() {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<StBuilding> bui;
    for (auto &building : buildings)
        bui.push_back({building.getID(),
                       building.getType(),
                       building.getPosition(),
                       building.getHP(),
                       building.getPlayerID()});
    return bui;
}

std::vector<StUnit> Game::getUnits() {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<StUnit> su;
    for (auto &unit : units)
        su.push_back({unit.getID(),
                      unit.getType(),
                      unit.getPosition(),
                      unit.getHeading(),
                      unit.getHP(),
                      unit.getPlayerID(),
                      unit.getAttacking()});

    for (auto &harvester : harvesters)
        su.push_back({harvester.getID(),
                      10,
                      harvester.getPosition(),
                      harvester.getHeading(),
                      harvester.getHP(),
                      harvester.getPlayerID()});
    return su;
}

std::vector<StOnHold> Game::getOnHold() {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<StOnHold> soh;
    for (auto &unit : unitsOnHold)
        soh.push_back({unit.getType(),
                       unit.getPlayerID(),
                       unit.getPercentage()});

    for (auto &harvester : harvestersOnHold)
        soh.push_back({10,
                       harvester.getPlayerID(),
                       harvester.getPercentage()});
    return soh;
}

void Game::advance() {
    std::lock_guard<std::mutex> lock(mut);
    playerRemoval();
    addOnHold();
    for (auto &unit : units) {
        unit.advance(*this);
    }
    for (auto &harvester : harvesters) {
        harvester.advance(*this);
    }
    worm.advance(*this);
    removeDead();
    if (checkGameEnd()) {
        // std::cout << "game should end" << std::endl;
    }
}

void Game::removeDead() {
    std::vector<Building> auxB;
    for (auto &building : buildings)
        if (!buildingRemoval(building))
            auxB.push_back(std::move(building));
    buildings = std::move(auxB);

    std::vector<Unit> auxU;
    for (auto &unit : units)
        if (unit.getHP() > 0)
            auxU.push_back(std::move(unit));
    units = std::move(auxU);

    std::vector<Harvester> auxH;
    for (auto &harvester : harvesters)
        if (harvester.getHP() > 0)
            auxH.push_back(std::move(harvester));
    harvesters = std::move(auxH);
}

bool Game::buildingRemoval(Building &building) {
    if (building.getHP() <= 0) {
        if (building.getType() == CONSTRUCTION_YARD)
            playerInfo[building.getPlayerID()].playerLost();
        updateCapacity(building);
        updateEnergy(building);
        map.setUnused(building);
        return true;
    }
    return false;
}

Targetable *Game::getTargetByID(int id) {
    if (id == -1)
        return nullptr;
    for (auto &building : buildings) {
        if (building.getID() == id) {
            // std::cout << "found building with id: " << id << std::endl;
            return &building;
        }
    }
    for (auto &harvester : harvesters) {
        if (harvester.getID() == id) {
            // std::cout << "found building with id: " << id << std::endl;
            return &harvester;
        }
    }
    for (auto &unit : units) {
        if (unit.getID() == id) {
            // std::cout << "found unit with id: " << id << std::endl;
            return &unit;
        }
    }
    return nullptr;
}

Targetable *Game::getTargetInRange(Unit &idleUnit) {
    for (auto &building : buildings) {
        if (idleUnit.getPlayerID() != building.getPlayerID() && idleUnit.inRange(&building))
            return &building;
    }
    for (auto &harvester : harvesters) {
        if (idleUnit.getPlayerID() != harvester.getPlayerID() && idleUnit.inRange(&harvester))
            return &harvester;
    }
    for (auto &unit : units) {
        if (idleUnit.getPlayerID() != unit.getPlayerID() && idleUnit.inRange(&unit)) {
            return &unit;
        }
    }
    return nullptr;
}

Targetable *Game::getTargetInRange(Worm &worm) {
    for (auto &harvester : harvesters) {
        if (worm.inRange(&harvester, worm.getSearchRange())) {
            return &harvester;
        }
    }
    for (auto &unit : units) {
        if (worm.inRange(&unit, worm.getSearchRange())) {
            return &unit;
        }
    }
    return nullptr;
}

Targetable *Game::getClosestRefinery(Harvester &cosechadora) {
    Targetable *closest = nullptr;
    for (auto &building : buildings) {
        if (!closest && building.getType() == TYPE_REFINERY && building.getPlayerID() == cosechadora.getPlayerID()) {
            closest = &building;
            continue;
        }
        if (building.getType() != TYPE_REFINERY)
            continue;
        closest = cosechadora.getDistance(closest) <= cosechadora.getDistance(&building) ? closest : &building;
    }
    return closest;
}

void Game::mover(SMsgMover *sMsgMover) {
    std::lock_guard<std::mutex> lock(mut);
    std::vector<int> unitsIDs = sMsgMover->getUnitsIDs();
    for (auto &unit : units)
        if (std::find(unitsIDs.begin(), unitsIDs.end(), unit.getID()) != unitsIDs.end()) {
            unit.reset();  // Esto resetea las variables para que deje de atacar, moverse y demás.
            unit.moveTo(sMsgMover->getDestination(), *this);
        }
    for (auto &harvester : harvesters)
        if (std::find(unitsIDs.begin(), unitsIDs.end(), harvester.getID()) != unitsIDs.end()) {
            harvester.reset();  // Esto resetea las variables para que deje de atacar, moverse y demás.
            harvester.moveTo(sMsgMover->getDestination(), *this);
        }
}

void Game::construir(SMsgConstruir *sMsgConstruir) {
    std::lock_guard<std::mutex> lock(mut);
    Building building(config.getAssets(), sMsgConstruir->getType(), sMsgConstruir->getPosition(), uniqueID,
                      sMsgConstruir->getPlayerID());
    if (!map.positionIsValid(building, sMsgConstruir->getPosition()) ||
        !hasRequiredMoney(building.getCost(), building.getPlayerID()))
        return;
    buildings.push_back(std::move(building));
    map.setUsed(building);
    subtractSpentMoney(building.getCost(), building.getPlayerID());
    updateCapacity(building);
    updateEnergy(building);
}

void Game::crearUnidad(SMsgCrearUnidad *sMsgCrearUnidad) {
    std::lock_guard<std::mutex> lock(mut);
    if (sMsgCrearUnidad->getType() == TYPE_COSECHADORA) {
        crearCosechadora(sMsgCrearUnidad);
        return;
    }
    Unit unit(config.getAssets(), sMsgCrearUnidad->getType(), sMsgCrearUnidad->getPosition(), uniqueID,
              sMsgCrearUnidad->getPlayerID());
    if (hasRequiredBuildings(unit) && hasRequiredMoney(unit.getCost(), unit.getPlayerID())) {
      std::pair<int, int> pos = getPositionOfBuildingType(unit.getRequired().front(), unit.getPlayerID());
      unit.setPosition(pos);
      subtractSpentMoney(unit.getCost(), unit.getPlayerID());
      UnitOnHold unitOnHold(std::move(unit), playerInfo[sMsgCrearUnidad->getPlayerID()].getEnergyPercentage());
      unitsOnHold.push_back(std::move(unitOnHold));
    }
}

void Game::crearCosechadora(SMsgCrearUnidad *sMsgCrearUnidad) {
    Harvester harvester(config.getAssets(), sMsgCrearUnidad->getPosition(), uniqueID,
                        sMsgCrearUnidad->getPlayerID());
    if (hasRequiredBuildings(harvester) && hasRequiredMoney(harvester.getCost(), harvester.getPlayerID())) {
      std::pair<int, int> pos = getPositionOfBuildingType(harvester.getRequired().front(), harvester.getPlayerID());
      harvester.setPosition(pos);
      subtractSpentMoney(harvester.getCost(), harvester.getPlayerID());
      HarvesterOnHold HarvesterOnHold(std::move(harvester), playerInfo[sMsgCrearUnidad->getPlayerID()].getEnergyPercentage());
      harvestersOnHold.push_back(std::move(HarvesterOnHold));
    }
}

void Game::atacar(SMsgAtacar *sMsgAtacar) {
    for (auto &unit : units) {
        if (std::find(sMsgAtacar->getUnitsIDs().begin(), sMsgAtacar->getUnitsIDs().end(), unit.getID()) !=
            sMsgAtacar->getUnitsIDs().end()) {
            unit.setTargetID(sMsgAtacar->getTargetID());
        }
    }
}

bool Game::hasRequiredBuildings(Harvester &harvester) {
    for (int i = 0; i < harvester.getRequired().size(); i++) {
        if (!buildingTypeExists(harvester.getRequired()[i], harvester.getPlayerID()))
            return false;
    }
    return true;
}

bool Game::hasRequiredBuildings(Unit &unit) {
    for (int i = 0; i < unit.getRequired().size(); i++) {
        if (!buildingTypeExists(unit.getRequired()[i], unit.getPlayerID()))
            return false;
    }
    return true;
}

bool Game::buildingTypeExists(int type, int playerID) {
    for (auto &building : buildings) {
        if (building.getType() == type && building.getPlayerID() == playerID) {
            return true;
        }
    }
    return false;
}

bool Game::hasRequiredMoney(int cost, int playerID) {
    return cost <= getPlayerMoney(playerID);
}

void Game::subtractSpentMoney(int quant, int playerID) {
    playerInfo[playerID].subtractMoney(quant);
}

void Game::addMoney(int quant, int playerID) {
    playerInfo[playerID].addMoney(quant);
}

int Game::getPlayerMoney(int playerID) {
    return playerInfo[playerID].getMoney();
}

void Game::updateCapacity(Building &building) {
    if (building.getHP() > 0)
        playerInfo[building.getPlayerID()].addCapacity(building.getCapacity());
    else
        playerInfo[building.getPlayerID()].subtractCapacity(building.getCapacity());
}

void Game::updateEnergy(Building &building) {
    if (building.getType() == TYPE_TRAMPA_AIRE) {
        if (building.getHP() > 0)
            playerInfo[building.getPlayerID()].addCurrentEnergy(building.getEnergy());
        else
            playerInfo[building.getPlayerID()].subtractCurrentEnergy(building.getEnergy());
    } else {
        if (building.getHP() > 0)
            playerInfo[building.getPlayerID()].addRequiredEnergy(building.getEnergy());
        else
            playerInfo[building.getPlayerID()].subtractRequiredEnergy(building.getEnergy());
    }
}

bool Game::checkGameEnd() {
    if (!started)
        return false;
    int count = 0;
    for (auto plInfo : playerInfo)
        if (plInfo.isPlaying())
            count++;
    if (count < 2) {
        notifyGameEnd();
        return true;
    }
    return forcedEnd;
}

std::vector<StPlayerInfo> const Game::getPlayersInfo() {
    std::vector<StPlayerInfo> res;
    for (auto plInfo : playerInfo) {
        res.push_back({plInfo.getPlayerID(),
                       plInfo.getCurrentEnergy(),
                       plInfo.getRequiredEnergy(),
                       plInfo.getMoney(),
                       plInfo.isPlaying(),
                       plInfo.isGameRunning(),
                       plInfo.getHouse()});
    }

    return res;
}

void Game::playerRemoval() {
    for (int i = 0; i < playerInfo.size(); i++) {
        if (playerInfo[i].isPlaying())
            continue;
        removeAll(i);
    }
}

void Game::removeAll(int playerID) {
    std::vector<Building> auxB;
    for (auto &building : buildings) {
        if (building.getPlayerID() != playerID)
            auxB.push_back(std::move(building));
    }
    buildings = std::move(auxB);

    std::vector<Unit> auxU;
    for (auto &unit : units) {
        if (unit.getPlayerID() != playerID)
            auxU.push_back(std::move(unit));
    }
    units = std::move(auxU);

    std::vector<Harvester> auxH;
    for (auto &harvester : harvesters) {
        if (harvester.getPlayerID() != playerID)
            auxH.push_back(std::move(harvester));
    }
    harvesters = std::move(auxH);
}

StWorm const Game::getWorm() {
    return {worm.getTargetPosition(), worm.getAttacking()};
}

void Game::reduceSpiceLevel(std::pair<int, int> pos) {
    map.reduceSpiceLevel(pos);
}

void Game::addOnHold() {
    for (auto &harvester : harvestersOnHold) {
        if (harvester.isReady()) {
            harvesters.push_back(std::move(harvester.getHarvester()));
        }
    }
    for (auto &unit : unitsOnHold) {
        if (unit.isReady()) {
            units.push_back(std::move(unit.getUnit()));
        }
    }
    cleanForRemoval();
}

void Game::cleanForRemoval() {
    std::vector<UnitOnHold> auxU;
    for (auto &unit : unitsOnHold)
        if (!unit.isForRemoval())
            auxU.push_back(std::move(unit));
    unitsOnHold = std::move(auxU);

    std::vector<HarvesterOnHold> auxH;
    for (auto &harvester : harvestersOnHold)
        if (!harvester.isForRemoval())
            auxH.push_back(std::move(harvester));
    harvestersOnHold = std::move(auxH);
}

void Game::notifyGameEnd() {
    for (auto &player : playerInfo)
        player.setGameEnd();
}

void Game::destruir(SMsgDestruir *SMsgDestruir) {
    std::lock_guard<std::mutex> lock(mut);
    for (auto &building : buildings) {
        if (building.getID() == SMsgDestruir->getBuildingID() && building.getPlayerID() == SMsgDestruir->getPlayerID()) {
          std::cout << "building id: " << building.getID() << " y playerid: " << building.getPlayerID() << std::endl;
          std::cout << "msg b id: " << SMsgDestruir->getBuildingID() << " y msg playerID: " << SMsgDestruir->getPlayerID() << std::endl;
            building.setHP(0);
            addMoney(building.getCost() / 4, building.getPlayerID());
            return;
        }
    }
}

std::pair<int, int> Game::getPositionOfBuildingType(int type, int playerID) {
    std::pair<int, int> position;
    for (auto &building : buildings) {
        if (building.getType() == type && building.getPlayerID() == playerID) {
            position = building.getPosition();
            break;
        }
    }
    position.first -= position.first % 4; //redondeo
    position.second -= position.second % 4;
    return position;
}

void Game::stop() {
    forcedEnd = true;
}
