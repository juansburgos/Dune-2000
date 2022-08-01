#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <string>
#include <vector>

#include "protocol.h"

struct StGame {
    // cppcheck-suppress unusedStructMember
    std::string name;
    // cppcheck-suppress unusedStructMember
    int players;
    // cppcheck-suppress unusedStructMember
    int required;
};

class ServerProtocol : private Protocol {
    void sendCode(int i);

    void sendBuilding(const StBuilding &building);

    void sendUnit(const StUnit &unit);

    void sendPlayerInfo(const StPlayerInfo &info);

   public:
    explicit ServerProtocol(Socket peer);

    int receiveCodigo();

    void receiveCrear(int &casa, int &requeridos, std::string &name, std::string &mapa);

    void sendListado(const std::vector<StGame> &listado);

    void receiveUnirse(std::string &name, int &house);

    void sendRet(bool ret);

    void sendMap(std::vector<std::vector<int>> const &tiles);

    void sendBuildings(const std::vector<StBuilding> &buildings);

    void sendUnits(const std::vector<StUnit> &units);

    ServerProtocol(const ServerProtocol &) = delete;

    ServerProtocol &operator=(const ServerProtocol &) = delete;

    void sendMapas(std::vector<std::pair<std::string, int>> &mapas);

    void sendPlayerID(int id);

    void receiveMover(std::vector<int> &unitsIDs, std::pair<int, int> &destination);

    void receiveConstruir(int &type, int &playerID, std::pair<int, int> &position);

    void receiveCrearUnidad(int &type, int &playerID, std::pair<int, int> &position);

    void receiveDestruir(int &playerID, int &buildingID);

    void receiveAtacar(std::vector<int> &unitsIDs, int &atacadoID);

    void sendPlayersInfo(const std::vector<StPlayerInfo> &playersInfo);

    void sendWorm(const StWorm &worm);

    void sendOnHold(const std::vector<StOnHold> &onHold);

    void sendOnHold(const StOnHold &onHold);

    void stop();
};

#endif  // SERVERPROTOCOL_H
