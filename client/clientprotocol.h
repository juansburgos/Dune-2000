#ifndef CLIENTPROTOCOL_H
#define CLIENTPROTOCOL_H

#include <memory>
#include <string>
#include <vector>

#include "protocol.h"

class CMsgMover;

class CMsgConstruir;

class CMsgCrearUnidad;

class CMsgAtacar;

class CMsgDestruir;

struct StPartida {
    // cppcheck-suppress unusedStructMember
    std::string nombre;
    // cppcheck-suppress unusedStructMember
    int jugadores;
    // cppcheck-suppress unusedStructMember
    int requeridos;
};

class ClientProtocol : private Protocol {
    StBuilding receiveBuilding();

    StUnit receiveUnit();

   public:
    ClientProtocol(char *hostname, char *servicename);

    void sendCrear(int codCasa, int requeridos, const std::string &juego, const std::string &mapa);

    bool receiveRet();

    void sendUnirse(int codCasa, const std::string &juego);

    void sendListarJuegos();

    void sendListarMapas();

    std::vector<StPartida> receiveListadoJuegos();

    std::vector<std::pair<std::string, int>> receiveListadoMapas();

    std::vector<std::vector<int>> receiveMap();

    std::vector<StBuilding> receiveBuildings();

    std::vector<StUnit> receiveUnits();

    int receivePlayerID();

    void send(CMsgMover *cMsgMover);

    void send(CMsgConstruir *cMsgConstruir);

    void send(CMsgCrearUnidad *cMsgCrearUnidad);

    void send(CMsgAtacar *cMsgAtacar);

    void send(CMsgDestruir *cMsgDestruir);

    std::vector<StPlayerInfo> receivePlayersInfo();

    StPlayerInfo receivePlayerInfo();

    StWorm receiveWorm();

    std::vector<StOnHold> receiveOnHold();

    StOnHold receiveEachOnHold();

    void stop();
};

#endif  // CLIENTPROTOCOL_H
