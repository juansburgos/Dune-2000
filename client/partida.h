#ifndef CLIENT_PARTIDA_H_
#define CLIENT_PARTIDA_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <mutex>
#include <vector>

#include "protocol.h"

class Partida {
    std::vector<StBuilding> buildings;
    std::mutex mutBuildings;
    std::vector<StOnHold> onHolds;
    std::mutex mutOnHols;
    std::vector<StPlayerInfo> playersInfo;
    std::mutex mutPlayersInfo;
    std::vector<std::vector<int>> specia;
    std::mutex mutSpecia;
    std::vector<std::vector<int>> tiles;
    std::mutex mutTiles;
    std::vector<StUnit> units;
    std::mutex mutUnits;
    StWorm worm;
    std::mutex mutWorm;
    int house;
    std::mutex mutHouse;
    int playerID = 0;
    std::mutex mutPlayerID;
    bool gameEnded = false;
    std::mutex mutGameEnded;
    std::vector<int> unitsToCreate = {1, 3, 5};
    std::vector<int> buildingsToCreate = {0, 1, 2, 3, 4, 5, 6, 7};

   public:
    Partida() = default;

    // Setters
    void setBuildings(std::vector<StBuilding> buildings);

    void setHouse(int house);

    void setOnHold(std::vector<StOnHold> aOnHolds);

    void setPlayerID(int playerID);

    void setPlayersInfo(std::vector<StPlayerInfo> playersInfo);

    void setSpecia(std::vector<std::vector<int>> specia);

    void setTiles(std::vector<std::vector<int>> tiles);

    void setUnits(std::vector<StUnit> units);

    void setUnitsToCreate(std::vector<int> units);

    void setWorm(StWorm worm);

    void endGame();

    // Getters
    std::vector<StBuilding> &getBuildings();

    std::vector<int> &getBuildingsToCreate();

    int getEnergy();

    int getHouse();

    int getMoney();

    std::vector<std::vector<int>> &getSpecia();

    std::vector<std::vector<int>> &getTiles();

    int getPlayerID();

    std::vector<StUnit> &getUnits();

    std::vector<int> &getUnitsToCreate();

    StWorm &getWorm();

    int getPlayerHouse(int playerID);

    int getPercentOnHold(int type);

    bool getIsRunning();

    bool getHasLost();


    bool isGameEnded();
};

#endif  // CLIENT_PARTIDA_H_
