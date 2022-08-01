#ifndef THSENDER_H
#define THSENDER_H

#include "clientprotocol.h"
#include <map>
#include <string>
#include "clientqueue.h"
#include "partida.h"

class ThSender {
    ClientProtocol &&cProtocol;
    ClientQueue &&queue;
    Partida &&partida;
    bool&& lostConnection;
public:
    ThSender(ClientProtocol &cProtocol, ClientQueue &queue, Partida &partida, bool& lostConn);

    void run();
};

#endif //THSENDER_H
