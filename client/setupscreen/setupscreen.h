#ifndef DUNE_SETUPSCREEN_H
#define DUNE_SETUPSCREEN_H

#include "clientprotocol.h"
#include "menuMultiPlayer.h"
#include "conectServer.h"
#include "playerReproductor.h"
#include <QtWidgets>
#include <string>

class SetupScreen : public QWidget {
    public:
        explicit SetupScreen(QWidget *parent = 0);
        virtual ~SetupScreen();
        std::string obtenerIp();
        std::string obtenerPuerto();
        int obtenerHouse();
        void errorConexion();
        void mostrarMultiplayer();
        bool quieroSalir();
        void recibirConexion(ClientProtocol *protocol);
        bool conectado();
        void conexionExitosa();
        bool mostrarJuego();
        bool huboError();
        void viewConect();
        void salir();
        void reset();
    private:
        conectServer conectar;
        MenuMultiPlayer multiplayer;
        PlayerReproductor player;
        bool salirAplicacion;
        bool estaConectado;
        bool error;
        // Elementos de la ventana principal
        QPushButton buttonServer;
        QPushButton buttonExit;
        QGridLayout mainLayout;
        void iniciarWidget();
        void crearPrincipal();
        void setVisible();
        void mostrarMensajeDeExito(QString mensaje);
        void closeEvent(QCloseEvent *event);


};

#endif //DUNE_SETUPSCREEN_H
