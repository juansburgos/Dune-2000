#include "editor.h"

Editor::Editor(QWidget *parent) : QWidget(parent),
    buttonCrear("Crear", this), buttonEdit("Editar", this),
    buttonSalir("Salir", this), mainLayout(this) , crear(), editar() {
  
    this->iniciarWidget();
    mainLayout.setAlignment(Qt::AlignCenter);
    mainLayout.addWidget(&buttonCrear, QDialogButtonBox::ActionRole);
    mainLayout.addWidget(&buttonEdit, QDialogButtonBox::ActionRole);
    mainLayout.addWidget(&buttonSalir, QDialogButtonBox::ActionRole);


    connect(&buttonCrear, &QAbstractButton::clicked, this, &Editor::crearMapa);
    connect(&buttonEdit, &QAbstractButton::clicked, this, &Editor::editarMapa);
    connect(&buttonSalir, &QAbstractButton::clicked, qApp, &QApplication::quit);
    this->setLayout(&mainLayout);
}

void Editor::crearMapa() {
    this->crear.limpiar();
    this->crear.show();
    this->crear.asignarMainMenu(this);
    this->hide();
}

void Editor::editarMapa() {
    this->editar.limpiar();
    this->editar.show();
    this->editar.asignarMainMenu(this);
    this->hide();
}

void Editor::iniciarWidget() {
    // this->setFixedSize(800, 600);
    this->setWindowTitle("EDITOR DUNE 2000");
    this->setObjectName("Main");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/config.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

Editor::~Editor() {
}
