#ifndef SALAUNIRSE_H
#define SALAUNIRSE_H

#include <QtWidgets>
#include "clientprotocol.h"

class SalaUnirse : public QWidget{
    public:
        SalaUnirse(QWidget *parent = 0);
        virtual ~SalaUnirse();
        void asignarMenuAnterior(QWidget *menuAnte);
        void asignarNombreDePartida(QString nombre);
        void recibirConexion(ClientProtocol *protocol);
        int obtenerHouse();
        bool estaJugando();
        bool quieroSalir();
        void reset() { jugando = false; }
    private:
        ClientProtocol *protocolo;
        QWidget *menuAnterior;
        // Elementos de la ventana
        QLabel namePartida;
        QLabel partidaLabel;
        QCheckBox checkAtrei;
        QCheckBox checkHarko;
        QCheckBox checkOrdos;
        QButtonGroup checkGroup;
        QLabel labelAtrei;
        QLabel labelHarko;
        QLabel labelOrdos;
        QPushButton buttonAtras;
        QPushButton buttonUnirse;
        QGridLayout gridUnirse;
        bool salir;
        int house;
        bool jugando;
        // Metodos privados
        void iniciarWidget();
        void unirseAPartida();
        void volverAMultiplayer();
        void seleccionarCasa();
        void mostrarMensajeDeExito(QString mensaje);
        void closeEvent(QCloseEvent *event);

};

#endif
