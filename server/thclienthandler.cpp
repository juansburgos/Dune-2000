#include "thclienthandler.h"
#include <iostream>
#include <utility>
#include <vector>
#include "protocolerror.h"
#include "smsgatacar.h"
#include "smsgconstruir.h"
#include "smsgcrearunidad.h"
#include "smsgdestruir.h"
#include "smsgmover.h"

ThClientHandler::ThClientHandler(Games &games, Socket peer) : sProtocol(std::move(peer)), games(games), running(true) {
}

void ThClientHandler::run() {
    bool is_closed = false;

    while (!is_closed) {
        try {
            int cod = sProtocol.receiveCodigo();
            if (cod == PROT_CREAR_PARTIDA_CODE) Crear();
            if (cod == PROT_LISTAR_JUEGOS_CODE) listarJuegos();
            if (cod == PROT_UNIRSE_CODE) unirse();
            if (cod == PROT_LISTAR_MAPAS_CODE) listarMapas();
            if (cod == PROT_MOVER_CODE) mover();
            if (cod == PROT_CONSTRUIR_CODE) construir();
            if (cod == PROT_CREAR_UNIDAD_CODE) crearUnidad();
            if (cod == PROT_ATACAR_CODE) atacar();
            if (cod == PROT_DESTRUIR_CODE) destruir();

        } catch (ProtocolError &e) {
            is_closed = true;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            is_closed = true;
        } catch (...) {
            std::cerr << "Error desconocido en recepcion de codigo"
                      << std::endl;
        }
    }
    running = false;
}

bool ThClientHandler::is_running() {
    return running;
}

void ThClientHandler::Crear() {
    int requeridos, casa;
    std::string nombre;
    std::string mapa;
    sProtocol.receiveCrear(casa, requeridos, nombre, mapa);
    bool ret = games.crear(nombre, mapa, requeridos, casa, sProtocol, queue);
    sProtocol.sendRet(ret);
    games.checkStarting();
}

void ThClientHandler::unirse() {
    std::string nombre;
    int house;
    sProtocol.receiveUnirse(nombre, house);
    bool ret = games.unirse(nombre, house, sProtocol, queue);
    sProtocol.sendRet(ret);
    games.checkStarting();
}

void ThClientHandler::listarJuegos() {
    std::vector<StGame> stGames = games.getStGames();
    sProtocol.sendListado(stGames);
}

void ThClientHandler::listarMapas() {
    std::vector<std::pair<std::string, int>> mapas = games.getMapas();
    sProtocol.sendMapas(mapas);
}

void ThClientHandler::destruir() {
    int buildingID;
    int playerID;
    sProtocol.receiveDestruir(playerID, buildingID);
    auto SMsgDestrui = std::make_shared<SMsgDestruir>(playerID, buildingID);
    queue->push(SMsgDestrui);
}

void ThClientHandler::mover() {
    std::vector<int> unitsIDs;
    std::pair<int, int> destination;
    sProtocol.receiveMover(unitsIDs, destination);
    auto sMsgMover = std::make_shared<SMsgMover>(unitsIDs, destination);
    queue->push(sMsgMover);
}

void ThClientHandler::construir() {
    int type;
    int playerID;
    std::pair<int, int> position;
    sProtocol.receiveConstruir(type, playerID, position);
    auto sMsgConstruir = std::make_shared<SMsgConstruir>(type, playerID, position);
    queue->push(sMsgConstruir);
}

void ThClientHandler::crearUnidad() {
    int type;
    int playerID;
    std::pair<int, int> position;
    sProtocol.receiveCrearUnidad(type, playerID, position);
    auto sMsgCrearUnidad = std::make_shared<SMsgCrearUnidad>(type, playerID, position);
    queue->push(sMsgCrearUnidad);
}

void ThClientHandler::atacar() {
    std::vector<int> unitsIDs;
    int atacadoID;
    sProtocol.receiveAtacar(unitsIDs, atacadoID);
    auto sMsgAtacar = std::make_shared<SMsgAtacar>(unitsIDs, atacadoID);
    queue->push(sMsgAtacar);
}

void ThClientHandler::stop() {
    games.stop();
    sProtocol.stop();
}
