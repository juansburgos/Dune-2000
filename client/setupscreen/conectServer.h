#ifndef CONECTSERVER_H
#define CONECTSERVER_H

#include <QtWidgets>
#include <string>

class conectServer : public QWidget {
    public:
        conectServer(QWidget *parent = 0);
        virtual ~conectServer();
        std::string getPuerto();
        std::string getIp();
        void asignarMenuAnterior(QWidget *menuAnte);
        bool establecerConexion();
        bool quieroSalir();
    private:
        QGridLayout vMainLayout;
        QLineEdit lineIp;
        QLabel ipLabel;
        QLabel puertoLabel;
        QLineEdit linePuerto;
        QPushButton buttonConect;
        QPushButton buttonAtras;
        //QHBoxLayout hLayoutPuerto;
        //QHBoxLayout hLayoutIp;
        //QHBoxLayout hButton;
        std::string ip;
        std::string puerto;
        QWidget *menuAnterior;
        bool conexion;
        bool salir;
        void conectar();
        void iniciarWidget();
        void irAMenuPrincipal();
        void closeEvent(QCloseEvent *event);
};

#endif
