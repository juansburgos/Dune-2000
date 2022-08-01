#include "clientprotocol.h"

#include <utility>
#include <vector>

#include "cmsgatacar.h"
#include "cmsgconstruir.h"
#include "cmsgcrearunidad.h"
#include "cmsgdestruir.h"
#include "cmsgmover.h"
#include "protocol.h"

ClientProtocol::ClientProtocol(char *hostname, char *servicename)
    : Protocol(std::move(Socket(hostname, servicename))) {
}

void ClientProtocol::sendCrear(int codCasa, int requeridos,
                               const std::string &juego, const std::string &mapa) {
    sendUChar(PROT_CREAR_PARTIDA_CODE);
    sendUChar(codCasa);
    sendUChar(requeridos);
    sendName(juego);
    sendName(mapa);
}

bool ClientProtocol::receiveRet() {
    return receiveUChar();
}

void ClientProtocol::sendUnirse(int codCasa, const std::string &juego) {
    sendUChar(PROT_UNIRSE_CODE);
    sendUChar(codCasa);
    sendName(juego);
}

void ClientProtocol::sendListarJuegos() {
    sendUChar(PROT_LISTAR_JUEGOS_CODE);
}

void ClientProtocol::sendListarMapas() {
    sendUChar(PROT_LISTAR_MAPAS_CODE);
}

std::vector<StPartida> ClientProtocol::receiveListadoJuegos() {
    uint16_t cant = receive16();
    std::vector<StPartida> listado;
    for (int i = 0; i < cant; i++) {
        int jugadores = receiveUChar();
        int requeridos = receiveUChar();
        std::string nombre = receiveName();
        listado.push_back({nombre, jugadores, requeridos});
    }
    return listado;
}

std::vector<std::pair<std::string, int>> ClientProtocol::receiveListadoMapas() {
    uint16_t cant = receive16();
    std::vector<std::pair<std::string, int>> mapas;
    for (int i = 0; i < cant; i++) {
        std::string name = receiveName();
        int count = receiveUChar();
        mapas.push_back({name, count});
    }
    return mapas;
}

std::vector<std::vector<int>> ClientProtocol::receiveMap() {
    std::vector<std::vector<int>> mat;
    int cols = receive16();
    int rows = receive16();
    for (int r = 0; r < rows; r++) {
        std::vector<int> row;
        for (int c = 0; c < cols; c++)
            row.push_back(receive16());
        mat.push_back(row);
    }
    return mat;
}

std::vector<StBuilding> ClientProtocol::receiveBuildings() {
    std::vector<StBuilding> buildings;
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++) {
        buildings.push_back(receiveBuilding());
    }
    return buildings;
}

std::vector<StUnit> ClientProtocol::receiveUnits() {
    std::vector<StUnit> units;
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++) {
        units.push_back(receiveUnit());
    }
    return units;
}

StBuilding ClientProtocol::receiveBuilding() {
    int id = receive16();
    int type = receiveUChar();
    std::pair<int, int> position = receivePosition();
    int hp = receive16();
    int playerID = receiveUChar();
    return {id, type, position, hp, playerID};
}

StUnit ClientProtocol::receiveUnit() {
    int id = receive16();
    int type = receiveUChar();
    std::pair<int, int> position = receivePosition();
    int heading = receiveUChar();
    int hp = receive16();
    int playerID = receiveUChar();
    bool attacking = receiveUChar();
    return {id, type, position, heading, hp, playerID, attacking};
}

int ClientProtocol::receivePlayerID() {
    return receiveUChar();
}

void ClientProtocol::send(CMsgMover *cMsgMover) {
    sendUChar(PROT_MOVER_CODE);
    std::vector<int> unitsIDs = cMsgMover->getUnitsIDs();
    sendUChar(unitsIDs.size());
    for (auto &id : unitsIDs)
        send16(id);
    sendPosition(cMsgMover->getDestination());
}

void ClientProtocol::send(CMsgConstruir *cMsgConstruir) {
    sendUChar(PROT_CONSTRUIR_CODE);
    sendUChar(cMsgConstruir->getType());
    sendUChar(cMsgConstruir->getPlayerID());
    sendPosition(cMsgConstruir->getPosition());
}

void ClientProtocol::send(CMsgCrearUnidad *cMsgCrearUnidad) {
    sendUChar(PROT_CREAR_UNIDAD_CODE);
    sendUChar(cMsgCrearUnidad->getType());
    sendUChar(cMsgCrearUnidad->getPlayerID());
    sendPosition(cMsgCrearUnidad->getPosition());
}

void ClientProtocol::send(CMsgAtacar *cMsgAtacar) {
    sendUChar(PROT_ATACAR_CODE);
    std::vector<int> unitsIDs = cMsgAtacar->getUnitsIDs();
    sendUChar(unitsIDs.size());
    for (auto &id : unitsIDs)
        send16(id);
    send16(cMsgAtacar->getAtacadoID());
}

void ClientProtocol::send(CMsgDestruir *cMsgDestruir) {
    sendUChar(PROT_DESTRUIR_CODE);
    sendUChar(cMsgDestruir->getPlayerID());
    send16(cMsgDestruir->getBuildingId());
}

std::vector<StPlayerInfo> ClientProtocol::receivePlayersInfo() {
    std::vector<StPlayerInfo> info;
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++) {
        info.push_back(receivePlayerInfo());
    }
    return info;
}

StPlayerInfo ClientProtocol::receivePlayerInfo() {
    int playerId = receive16();
    int currentEnergy = receive16();
    int requiredEnergy = receive16();
    int money = receive16();
    bool isPlaying = receiveUChar();
    bool gameIsRunning = receiveUChar();
    int house = receive16();
    return {playerId, currentEnergy, requiredEnergy, money, isPlaying, gameIsRunning, house};  // PASAR REQUIRED ENERGY;
}

StWorm ClientProtocol::receiveWorm() {
    std::pair<int, int> position = receivePosition();
    bool attacking = receiveUChar();
    return {position, attacking};
}

std::vector<StOnHold> ClientProtocol::receiveOnHold() {
    std::vector<StOnHold> onHold;
    int cant = receiveUChar();
    for (int i = 0; i < cant; i++) {
        onHold.push_back(receiveEachOnHold());
    }
    return onHold;
}

StOnHold ClientProtocol::receiveEachOnHold() {
    int type = receiveUChar();
    int playerId = receiveUChar();
    int percentage = receive16();
    return {type, playerId, percentage};
}

void ClientProtocol::stop() {
    Protocol::stop();
}