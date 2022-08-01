#ifndef THCLIENTHANDLER_H
#define THCLIENTHANDLER_H

#include <atomic>
#include <string>

#include "games.h"
#include "serverprotocol.h"
#include "serverqueue.h"
#include "socket.h"
#include "thread.h"

class ThClientHandler : public Thread {
    ServerProtocol sProtocol;
    Games &games;
    std::atomic<bool> running;
    ServerQueue *queue;

    void Crear();

    void listarJuegos();

    void listarMapas();

    void unirse();

    void mover();

    void construir();

    void destruir();

    void crearUnidad();

   public:
    ThClientHandler(Games &games, Socket peer);

    void run() override;

    bool is_running();

    void atacar();

    void stop();
};

#endif  // THCLIENTHANDLER_H
