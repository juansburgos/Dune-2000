#ifndef MENUMULTIPLAYER_H
#define MENUMULTIPLAYER_H

#include "clientprotocol.h"
#include "salaCrear.h"
#include "salaUnirse.h"
#include <QtWidgets>
#include <QtMultimedia>
#include "playerReproductor.h"

class MenuMultiPlayer : public QWidget {
    public:
        MenuMultiPlayer(QWidget *parent = 0);
        virtual ~MenuMultiPlayer();
        void asignarMenuAnterior(QWidget *menuAnte);
        void recibirConexion(ClientProtocol *protocol);
        int obtenerHouse();
        void establecerConexion();
        bool quieroSalir();
        bool estaJugando();
        void asignarPlayList(PlayerReproductor *player);
        void reset() {
                        crear.reset();
                        unirse.reset();
                        conectado = false;
                    }
    private:
        SalaCrear crear;
        SalaUnirse unirse;
        QWidget *menuAnterior;
        PlayerReproductor *playList;
        bool conectado;
        bool salir;
        // Elementos del Widget
        ClientProtocol *protocolo;
        QListWidget listaPartida;
        QPushButton buttonCrear;
        QPushButton buttonUnirse;
        QPushButton buttonActuali;
        QPushButton buttonAtras;
        QButtonGroup groupMultiplayer;
        QGridLayout mainLayout;
        // Metodos privados
        void iniciarWidget();
        void volverAlMain();
        void crearPartida();
        void mostrarListaDePartidas();
        void unirseAPartida();
        void closeEvent(QCloseEvent *event);

};

#endif
