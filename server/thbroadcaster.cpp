#include <iostream>
#include "thbroadcaster.h"
#include "protocolerror.h"
#include "serverprotocol.h"
#include "defines.h"

ThBroadcaster::ThBroadcaster(Game *aGame, ServerProtocol &sProtocol) {
    game = aGame;
    protocols.push_back({sProtocol});
}

void ThBroadcaster::add(ServerProtocol &sProtocol) {
    protocols.push_back(sProtocol);
}

void ThBroadcaster::run() {
    while (!game->checkGameEnd()) {
        count++;
        auto start = std::chrono::steady_clock::now();
        sendUpdate();
        auto end = std::chrono::steady_clock::now();
        int processTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (1000 / TPS_SERVER > processTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / TPS_SERVER - processTime));
        } else {
            std::cout << "[Broadcaster]  TPS Muy Elevado.  Process-time: " << processTime << "  Ratio: 1/" << count
                      << std::endl;
            count = 0;
        }
    }
    sendUpdate();
}

void ThBroadcaster::sendUpdate() {
    std::vector<std::reference_wrapper<ServerProtocol>> aux;
    for (auto &sProtocol: protocols) {
        try {
            sProtocol.get().sendOnHold(game->getOnHold());
            sProtocol.get().sendPlayersInfo(game->getPlayersInfo());
            sProtocol.get().sendMap(game->getSpecia());
            sProtocol.get().sendUnits(game->getUnits());
            sProtocol.get().sendBuildings(game->getBuildings());
            sProtocol.get().sendWorm(game->getWorm());
            aux.push_back(sProtocol);
        } catch (ProtocolError &e) {
            std::cout << "Se desconectó un Cliente." << std::endl;
        }
    }
    protocols = std::move(aux);
}

void ThBroadcaster::sendSetup() {
    int playerID = 0;
    for (auto &sProtocol: protocols) {
        sProtocol.get().sendPlayerID(playerID);
        sProtocol.get().sendMap(game->getTiles());
        sProtocol.get().sendMap(game->getSpecia());
        sProtocol.get().sendBuildings(game->getBuildings());
        sProtocol.get().sendUnits(game->getUnits());
        playerID++;
    }
}
