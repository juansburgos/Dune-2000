#ifndef DUNE_EDITOR_H
#define DUNE_EDITOR_H

#include "crearMenu.h"
#include "editarMenu.h"
#include <QtWidgets>

class Editor : public QWidget {
    public:
        explicit Editor(QWidget *parent = 0);
        virtual ~Editor();
    private:
        CrearMenu crear;
        EditarMenu editar;
        // Elementos del Widget
        QVBoxLayout mainLayout;
        QPushButton buttonCrear;
        QPushButton buttonEdit;
        QPushButton buttonSalir;

        // Metodos privados
        void iniciarWidget();
        void crearMapa();
        void editarMapa();
};


#endif //DUNE_EDITOR_H
