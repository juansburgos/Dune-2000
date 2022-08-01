#ifndef DUNE_THRECEIVER_H
#define DUNE_THRECEIVER_H


#include "clientprotocol.h"
#include "partida.h"

class ThReceiver {
    ClientProtocol &&cProtocol;
    Partida &&partida;
    bool&& lostConnection;

    void receiveSetup();

public:
    ThReceiver(ClientProtocol &cProtocol, Partida &partida, bool& lostConn);

    void run();
};


#endif //DUNE_THRECEIVER_H
