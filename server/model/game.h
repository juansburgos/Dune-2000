#ifndef DUNE_GAME_H
#define DUNE_GAME_H

#include <mutex>
#include <string>

#include "../smsgatacar.h"
#include "harvester.h"
#include "map.h"
#include "onhold.h"
#include "playerinfo.h"
#include "protocol.h"
#include "worm.h"

class SMsgMover;

class SMsgConstruir;

class SMsgCrearUnidad;

class SMsgDestruir;

class Game {
    std::mutex mut;
    Config config;
    int uniqueID = 0;
    std::string name;
    int players = 0;
    int required;
    bool started = false;
    bool forcedEnd = false;
    Map map;
    std::vector<PlayerInfo> playerInfo;
    std::vector<Building> buildings;
    std::vector<Unit> units;
    std::vector<Harvester> harvesters;
    std::vector<HarvesterOnHold> harvestersOnHold;
    std::vector<UnitOnHold> unitsOnHold;
    Worm worm;

    void removeDead();

    bool hasRequiredBuildings(Unit &unit);

    bool hasRequiredMoney(int cost, int playerID);

    bool buildingTypeExists(int type, int playerID);

    int getPlayerMoney(int playerID);

    void subtractSpentMoney(int quant, int playerID);

    void updateEnergy(Building &building);

    void updateCapacity(Building &building);

    bool buildingRemoval(Building &building);

    void playerRemoval();

    void removeAll(int playerID);

   public:
    Game(std::string name, const std::string &mapName, int required, int house);

    int getPlayers() const { return players; }

    int getRequired() const { return required; }

    std::string const &getName() { return name; }

    bool unirse(int &house);

    bool checkStarting();

    void advance();

    Game(Game &&other) noexcept = default;

    Game(const Game &) = delete;

    Game &operator=(const Game &) = delete;

    std::vector<std::vector<int>> const &getTiles();

    std::vector<std::vector<int>> const &getSpecia();

    std::vector<StBuilding> getBuildings();

    std::vector<StUnit> getUnits();

    Targetable *getTargetByID(int id);

    Targetable *getTargetInRange(Unit &idleUnit);

    Targetable *getTargetInRange(Worm &worm);

    Targetable *getClosestRefinery(Harvester &cosechadora);

    void mover(SMsgMover *sMsgMover);

    void construir(SMsgConstruir *sMsgContruir);

    void crearUnidad(SMsgCrearUnidad *sMsgCrearUnidad);

    void atacar(SMsgAtacar *sMsgAtacar);

    Map const &getMap() { return map; }

    std::vector<StPlayerInfo> const getPlayersInfo();

    StWorm const getWorm();

    void crearCosechadora(SMsgCrearUnidad *sMsgCrearUnidad);

    bool hasRequiredBuildings(Harvester &harvester);

    void addMoney(int quant, int playerID);

    void reduceSpiceLevel(std::pair<int, int> pos);

    void addOnHold();

    void cleanForRemoval();

    std::vector<StOnHold> getOnHold();

    bool checkGameEnd();

    void notifyGameEnd();

    void destruir(SMsgDestruir *SMsgDestruir);

    std::pair<int, int> getPositionOfBuildingType(int type, int playerID);

    void stop();
};

#endif  // DUNE_GAME_H
