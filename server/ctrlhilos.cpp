#include "ctrlhilos.h"
#include "thclienthandler.h"
#include "accepterror.h"
#include "thgamestatus.h"
#include <thread>
#include <vector>
#include <utility>

CtrlHilos::CtrlHilos(char *servicename) : srv(servicename), continuar(true) {
}

void CtrlHilos::run() {
    std::thread aceptador = std::thread(&CtrlHilos::aceptar, this);

    int c;
    do {
        c = getchar();
    } while (c != 'q');

    for (auto cHandler : clientHandlers)
        cHandler->stop();

    continuar = false;

    srv.shutdown(2);
    srv.close();

    aceptador.join();
}

void CtrlHilos::limpiarHilosTerminados() {
    for (auto it = clientHandlers.begin(); it != clientHandlers.end();) {
        if (!(*it)->is_running()) {
            (*it)->join();
            delete *it;
            it = clientHandlers.erase(it);
        } else {
            ++it;
        }
    }
}

void CtrlHilos::aceptar() {
    Games games;
    auto* gameStatus = new ThGameStatus(games, continuar);
    gameStatus->start();
    do {
        try {
            Socket peer = srv.accept();
            if (continuar) {
                auto *thClientHandler = new ThClientHandler(games, std::move(peer));
                thClientHandler->start();
                clientHandlers.push_back(thClientHandler);
            }
        } catch (AcceptError &e) {}
        limpiarHilosTerminados();
    } while (continuar);


    for (auto &hilo: clientHandlers) {
        hilo->join();
        delete hilo;
    }
    gameStatus->join();
}
