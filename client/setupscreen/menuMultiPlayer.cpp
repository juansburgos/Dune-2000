#include "menuMultiPlayer.h"

MenuMultiPlayer::MenuMultiPlayer(QWidget *parent) : QWidget(parent),
    listaPartida(this), crear(), menuAnterior(nullptr),
    buttonCrear("Crear Partida", this), unirse(),
    buttonUnirse("Unirse", this), buttonActuali("Actualizar", this),
    buttonAtras("Atras", this), groupMultiplayer(this), //contenedor(),
    mainLayout(this), conectado(false), salir(false) {
    
    this->iniciarWidget();
    buttonCrear.setAutoDefault(false);
    buttonAtras.setCheckable(true);
    buttonAtras.setAutoDefault(false);
    
    groupMultiplayer.addButton(&buttonCrear, 1);
    groupMultiplayer.addButton(&buttonUnirse, 2);
    groupMultiplayer.addButton(&buttonActuali, 3);

    QVBoxLayout *layoutLista = new QVBoxLayout;
    layoutLista->addWidget(&listaPartida);

    QGroupBox *listaBox = new QGroupBox;
    listaBox->setLayout(layoutLista);
    listaBox->setTitle("Selecciona la partida");
    
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setSpacing(10);
    vLayout->setAlignment(Qt::AlignCenter);
    vLayout->addWidget(&buttonCrear);
    vLayout->addWidget(&buttonUnirse);
    vLayout->addWidget(&buttonActuali);
    vLayout->addWidget(&buttonAtras);

    QHBoxLayout *contenedor = new QHBoxLayout;
    contenedor->addWidget(listaBox);
    contenedor->addLayout(vLayout);

    // Menu de botones
    connect(&buttonCrear, &QAbstractButton::clicked, this,
            &MenuMultiPlayer::crearPartida);
    connect(&buttonUnirse, &QAbstractButton::clicked, this,
             &MenuMultiPlayer::unirseAPartida);
    connect(&buttonActuali, &QAbstractButton::clicked, this,
            &MenuMultiPlayer::mostrarListaDePartidas);
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &MenuMultiPlayer::volverAlMain);
    
    mainLayout.addLayout(contenedor, 1, 0, Qt::AlignCenter);
    this->setLayout(&mainLayout);
    this->hide();
    this->crear.hide();
    this->unirse.hide();
    if (this->conectado) {
        this->mostrarListaDePartidas();
    }
}

void MenuMultiPlayer::crearPartida() {
    this->crear.show();
    this->crear.asignarMenuAnterior(this);
    this->crear.recibirProtocolo(this->protocolo);
    this->crear.establecerConexion();
    this->hide();
}

void MenuMultiPlayer::establecerConexion() {
    this->conectado = true;
    this->mostrarListaDePartidas();
}

void MenuMultiPlayer::volverAlMain() {
    this->menuAnterior->show(); 
    this->hide();
    this->asignarMenuAnterior(nullptr);
}

void MenuMultiPlayer::recibirConexion(ClientProtocol *protocol) {
    this->protocolo = protocol;
}

void MenuMultiPlayer::iniciarWidget() {
    this->setFixedSize(800, 600);
    this->setWindowTitle("DUNE 2000");
    this->setObjectName("multiplayer");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/multiplayer.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

void MenuMultiPlayer::asignarMenuAnterior(QWidget *menuAnte) {
    this->menuAnterior = menuAnte;
}

void MenuMultiPlayer::mostrarListaDePartidas() {
    this->listaPartida.clear();
    this->protocolo->sendListarJuegos();
    std::vector<StPartida> listado = this->protocolo->receiveListadoJuegos();
    for (StPartida partida: listado) {
        this->listaPartida.addItem(QString::fromStdString(partida.nombre)+": "+
        QString::number(partida.jugadores)+"/"+
        QString::number(partida.requeridos));
    }
}

void MenuMultiPlayer::unirseAPartida() {
    std::string name;
    if (this->listaPartida.count() > 0) {
        QString partida = this->listaPartida.currentItem()->text();
        std::string party = partida.toStdString();
        for (size_t i = 0; i < party.length(); i++) {
            if (party.at(i) != ':') {
                name.push_back(party.at(i));
            } else {
                break;
            }
        }
    }
    this->unirse.show();
    this->unirse.asignarMenuAnterior(this);
    this->unirse.asignarNombreDePartida(name.data());
    this->unirse.recibirConexion(this->protocolo);
    this->hide();
}

int MenuMultiPlayer::obtenerHouse() {
    int house = this->crear.obtenerHouse();
    if (house >= 0) {
        return house;
    } else {
        house = this->unirse.obtenerHouse();
        if (house >= 0) {
            return house;
        }
    }
    return -1;
}

bool MenuMultiPlayer::estaJugando() {
    if (this->crear.estaJugando()) {
        this->playList->next();
        return true;
    }
    if (this->unirse.estaJugando()) {
        this->playList->next();
        return true;
    }
    return false;
}

void MenuMultiPlayer::asignarPlayList(PlayerReproductor *player) {
    this->playList = player;
}

void MenuMultiPlayer::closeEvent(QCloseEvent *event) {
    this->salir = true;
}

bool MenuMultiPlayer::quieroSalir() {
    if (this->crear.quieroSalir())
        return true;
    if (this->unirse.quieroSalir())
        return true;
    return this->salir;
}


MenuMultiPlayer::~MenuMultiPlayer() {
}
