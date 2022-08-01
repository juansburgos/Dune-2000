#ifndef EDITARMENU_H
#define EDITARMENU_H

#include <QtWidgets>
#include <utility>
#include <yaml-cpp/yaml.h>
#include "mapWidget.h"
#include "piecesMap.h"
#include "common/defines.h"

class EditarMenu : public QWidget {
    public:
        explicit EditarMenu(QWidget *parent = 0);
        virtual ~EditarMenu();
        void asignarMainMenu(QWidget *main);
        void limpiar();

    private:
        QString nameFile;
        YAML::Node map;
        QWidget *mainMenu;
        QLabel nameMenu;
        QPushButton buttonOpen;
        QPixmap mapaACrear;
        QListView trozosMapaList;
        MapWidget mapaWidget;
        PiecesMap* trozosMap;
        QPushButton buttonEditar;
        QPushButton buttonAtras;
        QGridLayout mainLayout;
        std::string nameTerrain;
        // Metodos Privados
        void iniciarWidget();
        void loadImage();
        void setupMapa();
        void agregarTilesBase();
        void volverAlMain();
        void editarMapa();
        void abrirArchivo();
        void cargarMapa();
        void cargarTrozosDeTerreno();
        void mostrarMensaje(QString mensaje);
        
};

#endif
