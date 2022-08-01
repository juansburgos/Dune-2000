#ifndef CTRLHILOS_H
#define CTRLHILOS_H

#include <list>
#include <atomic>
#include "thclienthandler.h"
#include "socket.h"

class CtrlHilos {
    Socket srv;
    std::list<ThClientHandler *> clientHandlers;

    std::atomic<bool> continuar;

    void aceptar();

    void limpiarHilosTerminados();

public:
    explicit CtrlHilos(char *servicename);

    void run();
};

#endif //CTRLHILOS_H
