#include "serverprotocol.h"

#include <utility>

ServerProtocol::ServerProtocol(Socket peer) : Protocol(std::move(peer)) {
}

int ServerProtocol::receiveCodigo() {
    return receiveUChar();
}

void ServerProtocol::receiveCrear(int &casa, int &requeridos, std::string &name, std::string &mapa) {
    casa = receiveUChar();
    requeridos = receiveUChar();
    name = receiveName();
    mapa = receiveName();
}

void ServerProtocol::sendListado(const std::vector<StGame> &listado) {
    send16(listado.size());
    for (auto &game : listado) {
        sendUChar(game.players);
        sendUChar(game.required);
        sendName(game.name);
    }
}

void ServerProtocol::receiveUnirse(std::string &name, int &house) {
    house = receiveUChar();
    name = receiveName();
}

void ServerProtocol::sendRet(bool ret) {
    sendUChar(ret);
}

void ServerProtocol::sendCode(int code) {
    sendUChar(code);
}

void ServerProtocol::sendMap(std::vector<std::vector<int>> const &map) {
    send16(map.size());     // rows
    send16(map[0].size());  // cols
    for (auto &row : map)
        for (auto cell : row)
            send16(cell);
}

void ServerProtocol::sendBuildings(const std::vector<StBuilding> &buildings) {
    sendUChar(buildings.size());
    for (auto &building : buildings)
        sendBuilding(building);
}

void ServerProtocol::sendBuilding(const StBuilding &building) {
    send16(building.id);
    sendUChar(building.type);
    sendPosition(building.position);
    send16(building.hp);
    sendUChar(building.playerID);
}

void ServerProtocol::sendUnits(const std::vector<StUnit> &units) {
    sendUChar(units.size());
    for (auto &unit : units)
        sendUnit(unit);
}

void ServerProtocol::sendOnHold(const std::vector<StOnHold> &onHold) {
    sendUChar(onHold.size());
    for (auto &each : onHold)
        sendOnHold(each);
}

void ServerProtocol::sendOnHold(const StOnHold &onHold) {
    sendUChar(onHold.type);
    sendUChar(onHold.playerID);
    send16(onHold.percentage);
}

void ServerProtocol::sendUnit(const StUnit &unit) {
    send16(unit.id);
    sendUChar(unit.type);
    sendPosition(unit.position);
    sendUChar(unit.heading);
    send16(unit.hp);
    sendUChar(unit.playerID);
    sendUChar(unit.attacking);
}

void ServerProtocol::sendMapas(std::vector<std::pair<std::string, int>> &mapas) {
    send16(mapas.size());
    for (auto &mapa : mapas) {
        sendName(mapa.first);
        sendUChar(mapa.second);
    }
}

void ServerProtocol::sendPlayerID(int id) {
    sendUChar(id);
}

void ServerProtocol::receiveMover(std::vector<int> &unitsIDs, std::pair<int, int> &destination) {
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++)
        unitsIDs.push_back(receive16());
    destination = receivePosition();
}

void ServerProtocol::receiveConstruir(int &type, int &playerID, std::pair<int, int> &position) {
    type = receiveUChar();
    playerID = receiveUChar();
    position = receivePosition();
}

void ServerProtocol::receiveCrearUnidad(int &type, int &playerID, std::pair<int, int> &position) {
    type = receiveUChar();
    playerID = receiveUChar();
    position = receivePosition();
}

void ServerProtocol::receiveAtacar(std::vector<int> &unitsIDs, int &atacadoID) {
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++)
        unitsIDs.push_back(receive16());
    atacadoID = receive16();
}

void ServerProtocol::receiveDestruir(int &playerID, int &buildingID) {
    playerID = receiveUChar();
    buildingID = receive16();
}

void ServerProtocol::sendPlayersInfo(const std::vector<StPlayerInfo> &playersInfo) {
    sendUChar(playersInfo.size());
    for (auto &playerInfo : playersInfo)
        sendPlayerInfo(playerInfo);
}

void ServerProtocol::sendPlayerInfo(const StPlayerInfo &info) {
    send16(info.playerID);
    send16(info.currentEnergy);
    send16(info.requiredEnergy);
    send16(info.money);
    sendUChar(info.isPlaying);
    sendUChar(info.gameRunnig);
    send16(info.house);
}

void ServerProtocol::sendWorm(const StWorm &worm) {
    sendPosition(worm.position);
    sendUChar(worm.attacking);
}

void ServerProtocol::stop() {
    Protocol::stop();
}
