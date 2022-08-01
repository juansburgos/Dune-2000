#ifndef CREARMENU_H
#define CREARMENU_H

#include "mapWidget.h"
#include "piecesMap.h"
#include <QtWidgets>

class CrearMenu : public QWidget {
    public:
        explicit CrearMenu(QWidget *parent = 0);
        virtual ~CrearMenu();
        void asignarMainMenu(QWidget *main);
        void limpiar();

    private:
        QWidget *mainMenu;
        QLabel nameMenu;
        QLabel labelName;
        QLineEdit lineName;
        // QLabel labelTiles;
        // QComboBox comboTiles;
        QLabel labelTam;
        QLineEdit tamMap;
        QPushButton buttonTamMap;
        QPixmap mapaACrear;
        QListView trozosMapaList;
        QPushButton buttonClean;
        MapWidget mapaWidget;
        PiecesMap* trozosMap;
        QPushButton buttonCrear;
        QPushButton buttonAtras;
        QGridLayout mainLayout;
        // Metodos privados
        void iniciarWidget();
        void volverAlMain();
        void loadImage();
        void setupMapa();
        void cambiarSizeMap();
        void mostrarListaDeTiles();
        void limpiarMapa();
        void guardarMapa();
        void agregarTilesBase();
        void mostrarMensaje(QString mensaje);

};

#endif
