#ifndef CLIENT_THDRAWER_H_
#define CLIENT_THDRAWER_H_

#include "clientqueue.h"
#include "partida.h"

class ThDrawer {
    Partida &&partida;
    ClientQueue &&queue;
    bool&& lostConnection;

   public:
    explicit ThDrawer(Partida &partida, ClientQueue &queue, bool& lostConn);
    void run();
};

#endif  // CLIENT_THDRAWER_H_
