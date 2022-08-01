#include "setupscreen.h"
#include <qapplication.h>
#include <qevent.h>

SetupScreen::SetupScreen(QWidget *parent) : QWidget(parent),
    salirAplicacion(false), conectar(), multiplayer(), player(),
    buttonServer("Multijugador", this), buttonExit("Salir", this),
    mainLayout(this), estaConectado(false), error(false) {

    this->iniciarWidget();
    this->crearPrincipal();
}

void SetupScreen::iniciarWidget() {
    this->setObjectName("Main");
    this->setWindowTitle("DUNE 2000");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile fileCss("../assets/css/config.qss");
    fileCss.open(QFile::ReadOnly);
    this->setFixedSize(800 ,600);
    this->setStyleSheet(fileCss.readAll());
}

void SetupScreen::crearPrincipal() {
    buttonServer.setCheckable(true);
    buttonServer.setAutoDefault(false);
    buttonExit.setDefault(true);
    QVBoxLayout *buttonBox = new QVBoxLayout;
    buttonBox->setAlignment(Qt::AlignCenter);
    buttonBox->addWidget(&buttonServer);
    buttonBox->addWidget(&buttonExit);

    connect(&buttonServer, &QAbstractButton::clicked, this,
            &SetupScreen::setVisible);
    connect(&buttonExit, &QAbstractButton::clicked, this, &SetupScreen::salir);

    mainLayout.addLayout(buttonBox, 0, 0, Qt::AlignCenter);
    this->setLayout(&mainLayout);
    this->conectar.hide();
}

void SetupScreen::setVisible() {
    if (this->estaConectado) {
        this->multiplayer.show();
        this->multiplayer.asignarMenuAnterior(this);
    } else {
        this->conectar.show();
        this->conectar.asignarMenuAnterior(this);
    }
    this->hide();
}

void SetupScreen::salir() {
    this->salirAplicacion = true;
    this->conectar.hide();
    this->hide();
    QApplication::quit();
}

bool SetupScreen::quieroSalir() {
    if (this->conectar.quieroSalir())
        return true;
    if (this->multiplayer.quieroSalir())
        return true;
    return this->salirAplicacion;
}

std::string SetupScreen::obtenerIp() {
    return this->conectar.getIp();
}

std::string SetupScreen::obtenerPuerto() {
    return this->conectar.getPuerto();
}

void SetupScreen::recibirConexion(ClientProtocol *protocol) {
    this->multiplayer.recibirConexion(protocol);
}

void SetupScreen::mostrarMensajeDeExito(QString mensaje) {
    QMessageBox::information(this, "Information", mensaje,
                            QMessageBox::Close);
}

SetupScreen::~SetupScreen() {
}

void SetupScreen::closeEvent(QCloseEvent *event) {
    this->salirAplicacion = true;
}

void SetupScreen::errorConexion() {
    this->error = true;
}

bool SetupScreen::huboError() {
    return this->error;
}

void SetupScreen::viewConect() {
    this->conectar.show();
    this->conectar.asignarMenuAnterior(this);
    this->mostrarMensajeDeExito("Conexion Fallida");
    this->hide();
}

int SetupScreen::obtenerHouse() {
    return this->multiplayer.obtenerHouse();
}

bool SetupScreen::conectado() {
    return this->estaConectado;
}

void SetupScreen::conexionExitosa() {
    this->estaConectado = true;
    this->error = false;
}

bool SetupScreen::mostrarJuego() {
    return this->multiplayer.estaJugando();
}

void SetupScreen::mostrarMultiplayer() {
    this->multiplayer.show();
    this->multiplayer.asignarMenuAnterior(this);
    this->multiplayer.asignarPlayList(&player);
    this->multiplayer.establecerConexion();
    this->conectar.hide();
    this->hide();
}

void SetupScreen::reset() {
  estaConectado = false;
  multiplayer.reset();
}
