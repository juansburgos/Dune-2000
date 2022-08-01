#include "threceiver.h"
#include <iostream>

ThReceiver::ThReceiver(ClientProtocol &cProtocol, Partida &partida, bool& lostConn) : cProtocol(std::move(cProtocol)),
                                                                      partida(std::move(partida)),
                                                                      lostConnection(std::move(lostConn)) {
}

void ThReceiver::receiveSetup() {
    partida.setPlayerID(cProtocol.receivePlayerID());
    partida.setTiles(cProtocol.receiveMap());
    partida.setSpecia(cProtocol.receiveMap());
    partida.setBuildings(cProtocol.receiveBuildings());
    partida.setUnits(cProtocol.receiveUnits());
}

void ThReceiver::run() {
    receiveSetup();

    while (true) {  // TDOO agregar fin
        try {
            partida.setOnHold(cProtocol.receiveOnHold());
            partida.setPlayersInfo(cProtocol.receivePlayersInfo());
            partida.setSpecia(cProtocol.receiveMap());
            partida.setUnits(cProtocol.receiveUnits());
            partida.setBuildings(cProtocol.receiveBuildings());
            partida.setWorm(cProtocol.receiveWorm());
        }
        catch (const std::exception &e) {
            lostConnection = true;
            std::cout << "Cierre de conexión" << std::endl;
            break;
        }
    }
}
