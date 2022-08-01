#include "partida.h"

void Partida::setBuildings(std::vector<StBuilding> somebuildingins) {
    std::lock_guard<std::mutex> lock(mutBuildings);
    buildings = std::move(somebuildingins);
}

std::vector<StBuilding> &Partida::getBuildings() {
    std::lock_guard<std::mutex> lock(mutBuildings);
    return buildings;
}

void Partida::setOnHold(std::vector<StOnHold> aOnHolds) {
    std::lock_guard<std::mutex> lock(mutOnHols);
    onHolds = std::move(aOnHolds);
}

void Partida::setTiles(std::vector<std::vector<int>> aTiles) {
    std::lock_guard<std::mutex> lock(mutTiles);
    tiles = std::move(aTiles);
}

void Partida::setSpecia(std::vector<std::vector<int>> aSpeicia) {
    std::lock_guard<std::mutex> lock(mutSpecia);
    specia = std::move(aSpeicia);
}

void Partida::setUnits(std::vector<StUnit> someUnits) {
    std::lock_guard<std::mutex> lock(mutUnits);
    units = std::move(someUnits);
}

std::vector<std::vector<int>> &Partida::getTiles() {
    std::lock_guard<std::mutex> lock(mutTiles);
    return tiles;
}

std::vector<std::vector<int>> &Partida::getSpecia() {
    std::lock_guard<std::mutex> lock(mutSpecia);
    return specia;
}

std::vector<StUnit> &Partida::getUnits() {
    std::lock_guard<std::mutex> lock(mutUnits);
    return units;
}

void Partida::setHouse(int playerHouse) {
    std::lock_guard<std::mutex> lock(mutHouse);
    house = playerHouse;
}

int Partida::getHouse() {
    std::lock_guard<std::mutex> lock(mutHouse);
    return house;
}

void Partida::setPlayerID(int playerID) {
    std::lock_guard<std::mutex> lock(mutPlayerID);
    this->playerID = playerID;
}

int Partida::getPlayerID() {
    std::lock_guard<std::mutex> lock(mutPlayerID);
    return playerID;
}

std::vector<int> &Partida::getUnitsToCreate() {
    return unitsToCreate;
}

std::vector<int> &Partida::getBuildingsToCreate() {
    return buildingsToCreate;
}

void Partida::setUnitsToCreate(std::vector<int> units) {
    unitsToCreate = std::move(units);
}

int Partida::getEnergy() {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    auto found = std::find_if(
        playersInfo.begin(), playersInfo.end(),
        [this](const StPlayerInfo &ptr) {
            return playerID == ptr.playerID;
        });

    if (found != std::end(playersInfo)) {
        return found->currentEnergy;
    }

    return 0;
}

int Partida::getMoney() {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    auto found = std::find_if(
        playersInfo.begin(), playersInfo.end(),
        [this](const StPlayerInfo &ptr) {
            return playerID == ptr.playerID;
        });

    if (found != std::end(playersInfo)) {
        return found->money;
    }
    return 0;
}

void Partida::setPlayersInfo(std::vector<StPlayerInfo> aPlayersInfo) {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    playersInfo = std::move(aPlayersInfo);
}

void Partida::setWorm(StWorm aWorm) {
    std::lock_guard<std::mutex> lock(mutWorm);
    worm = std::move(aWorm);
}

StWorm &Partida::getWorm() {
    std::lock_guard<std::mutex> lock(mutWorm);
    return worm;
}

int Partida::getPlayerHouse(int playerID) {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    auto found = std::find_if(
        playersInfo.begin(), playersInfo.end(),
        [playerID](const StPlayerInfo &ptr) {
            return playerID == ptr.playerID;
        });

    if (found != std::end(playersInfo)) {
        return found->house;
    }
    return 0;
}

int Partida::getPercentOnHold(int type) {
    std::lock_guard<std::mutex> lock(mutOnHols);
    auto found = std::find_if(
        onHolds.begin(), onHolds.end(),
        [type, this](const StOnHold &ptr) {
            return playerID == ptr.playerID && ptr.type == type;
        });

    if (found != std::end(onHolds)) {
        return found->percentage;
    }
    return 0;
}

bool Partida::getIsRunning() {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    auto found = std::find_if(
        playersInfo.begin(), playersInfo.end(),
        [this](const StPlayerInfo &ptr) {
            return playerID == ptr.playerID;
        });

    if (found != std::end(playersInfo)) {
        return found->gameRunnig;
    }
    return 0;
}

bool Partida::getHasLost() {
    std::lock_guard<std::mutex> lock(mutPlayersInfo);
    auto found = std::find_if(
        playersInfo.begin(), playersInfo.end(),
        [this](const StPlayerInfo &ptr) {
            return playerID == ptr.playerID;
        });

    if (found != std::end(playersInfo)) {
        return !found->isPlaying;
    }
    return 0;
}

void Partida::endGame() {
    std::lock_guard<std::mutex> lock(mutGameEnded);
    gameEnded = true;
}

bool Partida::isGameEnded() {
    std::lock_guard<std::mutex> lock(mutGameEnded);
    return gameEnded;
}