#include <iostream>
#include <exception>
#include <qapplication.h>
#include <string>
#include <thread>
#include "clientprotocol.h"
#include "thsender.h"
#include "threceiver.h"
#include "setupscreen.h"
#include "partida.h"
#include "thdrawer.h"
#include "clientqueue.h"

void createThSender(ClientProtocol &cProtocol, ClientQueue &queue, Partida &partida, bool& lostConn) {
    ThSender thSender(cProtocol, queue, partida, lostConn);
    thSender.run();
}

void createThReceiver(ClientProtocol &cProtocol, Partida &partida, bool& lostConn) {
    ThReceiver thReceiver(cProtocol, partida, lostConn);
    thReceiver.run();
}

void createThDrawer(Partida &partida, ClientQueue &queue, bool& lostConn) {
    ThDrawer thDrawer(partida, queue, lostConn);
    thDrawer.run();
}

int main(int argc, char *argv[]) {

    if (argc != 1) {
        std::cout << "Uso: ./dune_client" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        QApplication app(argc, argv);
        SetupScreen setupScr;
        while (!setupScr.quieroSalir()) {
            try {
                setupScr.huboError() ? setupScr.viewConect() : setupScr.show();
                app.exec();
                if (setupScr.quieroSalir())
                    break;
                if (!setupScr.conectado() || setupScr.huboError()) {
                    std::string hostname = setupScr.obtenerIp();
                    std::string servicename = setupScr.obtenerPuerto();
                    ClientProtocol cProtocol(hostname.data(), servicename.data());
                    setupScr.conexionExitosa();
                    setupScr.recibirConexion(&cProtocol);
                    setupScr.mostrarMultiplayer();
                    app.exec();
                    if (setupScr.mostrarJuego()) {
                        Partida partida;
                        partida.setHouse(setupScr.obtenerHouse());
                        ClientQueue queue;
                        bool lostConnection = false;
                        std::thread thDrawer(createThDrawer, std::ref(partida), std::ref(queue), std::ref(lostConnection));
                        std::thread thReceiver(createThReceiver, std::ref(cProtocol), std::ref(partida), std::ref(lostConnection));
                        std::thread thSender(createThSender, std::ref(cProtocol), std::ref(queue), std::ref(partida), std::ref(lostConnection));
                        thDrawer.join();
                        thSender.join();
                        cProtocol.stop();
                        thReceiver.join();
                        setupScr.reset();
                    } else if (setupScr.quieroSalir()) {
                        break;
                    }
                }
            } catch (std::exception &e) {
                setupScr.errorConexion();
            }
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Pasó algo raro!!!" << std::endl;
    }
}
