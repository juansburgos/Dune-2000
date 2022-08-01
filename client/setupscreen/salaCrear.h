#ifndef SALACREAR_H
#define SALACREAR_H

#include "clientprotocol.h"
#include <QtWidgets>

class SalaCrear : public QWidget {
    public:
        SalaCrear(QWidget *parent = 0);
        virtual ~SalaCrear();
        void asignarMenuAnterior(QWidget *menuAnte);
        void recibirProtocolo(ClientProtocol *protoc);
        int obtenerHouse();
        void establecerConexion();
        bool estaJugando();
        bool quieroSalir();
        void reset() {
                        conectado = false;
                        jugando = false;
                      }
    private:
        ClientProtocol *protocolo;
        QWidget *menuAnterior;
        int house;
        bool conectado;
        bool jugando;
        std::vector<std::pair<std::string, int>> listadoMapas;
        // Elementos de la ventana
        QLabel namePartida;
        QLineEdit linePartida;
        QLabel labelCantidad;
        QListWidget listaMapas;
        QComboBox comCantidad;
        QCheckBox checkAtrei;
        QCheckBox checkHarko;
        QCheckBox checkOrdos;
        QButtonGroup checkGroup;
        QPushButton buttonAtras;
        QPushButton buttonCrear;
        QGridLayout gridCrear;
        bool salir;
        // Metodos
        void iniciarWidget();
        void volverAlMultiplayer();
        void irAlaSalaDeEspera();
        void mostrarMensajeDeExito(QString mensaje);
        void mostrarListaDeMapas();
        void seleccionarCasa();
        void enviarCrearPartida(QString cantJug, QString nameParty,
                                QString nameMapa);
        void recibirListadoMapas();
        QString filtrarNombreDeMapa();
        void closeEvent(QCloseEvent *event);
};

#endif
