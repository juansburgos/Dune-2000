#include "salaCrear.h"
#include "clientprotocol.h"
#include "defines.h"
#include <qdebug.h>

SalaCrear::SalaCrear(QWidget *parent) : QWidget(parent),
        namePartida("Nombre de la Partida", this),
        linePartida(this), labelCantidad("Filtrar cantidad de Jugadores", this),
        comCantidad(this), checkAtrei("Atreides", this),
        checkHarko("Harkonnen", this), checkOrdos("Ordos", this),
        checkGroup(this), buttonAtras("Atras", this),
        buttonCrear("Crear", this), gridCrear(this), house(-1),
        conectado(false), listaMapas(this), jugando(false), salir(false) {

    this->iniciarWidget();
    namePartida.setBuddy(&linePartida);
    QHBoxLayout *hLayoutName = new QHBoxLayout;
    hLayoutName->addWidget(&namePartida);
    hLayoutName->addWidget(&linePartida);

    // Selecciono cantidad de jugadores en la partida
    // Modificar la cantidad de jugadores por partida
    QStringList cantidad = {"2", "3", "4"};
    comCantidad.addItems(cantidad);
    QHBoxLayout *hLayoutCant = new QHBoxLayout;
    hLayoutCant->addWidget(&labelCantidad);
    hLayoutCant->addWidget(&comCantidad);

    QHBoxLayout *layoutInfo = new QHBoxLayout;
    layoutInfo->setSpacing(15);
    layoutInfo->addLayout(hLayoutName);
    layoutInfo->addLayout(hLayoutCant);

    // Selecciono Casa
    checkAtrei.setObjectName("Atreides");
    checkAtrei.setChecked(true);
    checkHarko.setObjectName("Harkonnen");
    checkHarko.setChecked(false);
    checkOrdos.setObjectName("Ordos");
    checkOrdos.setChecked(false);
    checkGroup.addButton(&checkAtrei, HOUSE_ATREIDES);
    checkGroup.addButton(&checkHarko, HOUSE_HARKONNEN);
    checkGroup.addButton(&checkOrdos, HOUSE_ORDOS);

    QVBoxLayout *checkLayout = new QVBoxLayout;
    checkLayout->addWidget(&checkAtrei);
    checkLayout->addWidget(&checkHarko);
    checkLayout->addWidget(&checkOrdos);

    QVBoxLayout *layoutGroup = new QVBoxLayout;
    layoutGroup->addLayout(checkLayout, Qt::AlignCenter);

    QGroupBox *casaBox = new QGroupBox;
    casaBox->setLayout(layoutGroup);
    casaBox->setTitle("Selecciona tu Casa");

    QVBoxLayout *layoutLista = new QVBoxLayout;
    layoutLista->addWidget(&listaMapas);

    QGroupBox *listaBox = new QGroupBox;
    listaBox->setLayout(layoutLista);
    listaBox->setTitle("Selecciona el Mapa");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(25);
    layout->setMargin(8);
    layout->addWidget(listaBox);
    layout->addWidget(casaBox);

    // crear y atras
    QHBoxLayout *finalLayout = new QHBoxLayout;
    finalLayout->setSpacing(10);
    finalLayout->addWidget(&buttonAtras);
    finalLayout->addWidget(&buttonCrear);

    connect(&comCantidad, &QComboBox::currentTextChanged, this,
            &SalaCrear::mostrarListaDeMapas);
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &SalaCrear::volverAlMultiplayer);
    connect(&buttonCrear, &QAbstractButton::clicked, this,
            &SalaCrear::irAlaSalaDeEspera);

    // Presentacion de pantalla Crear
    gridCrear.setVerticalSpacing(20);
    gridCrear.addLayout(layoutInfo, 0, 0, Qt::AlignCenter);
    gridCrear.addLayout(layout, 1, 0, Qt::AlignCenter | Qt::AlignTop);
    gridCrear.addLayout(finalLayout, 2, 0, Qt::AlignCenter);
    this->setLayout(&gridCrear);
}

void SalaCrear::iniciarWidget() {
    this->setFixedSize(800, 600);
    this->setWindowTitle("DUNE 2000");
    this->setObjectName("crear");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/crear.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

void SalaCrear::volverAlMultiplayer() {
    this->menuAnterior->show();
    this->hide();
    this->asignarMenuAnterior(nullptr);
}

void SalaCrear::asignarMenuAnterior(QWidget *menuAnte) {
    this->menuAnterior = menuAnte;
}

void SalaCrear::irAlaSalaDeEspera() {
    QString nameParty = this->linePartida.text();
    if (nameParty.isEmpty()) {
        mostrarMensajeDeExito("Agregue nombre de partida");
    } else {
        QString number = this->comCantidad.currentText();
        this->seleccionarCasa();
        if (this->listaMapas.selectedItems().count() == 0) {
            this->mostrarMensajeDeExito("Selecciona un Mapa");
        } else {
            QString nameMapa = filtrarNombreDeMapa();
            this->enviarCrearPartida(number, nameParty, nameMapa);
        }
    }
}

QString SalaCrear::filtrarNombreDeMapa() {
    QString name;
    if (this->listaMapas.count() > 0) {
        QString partida = this->listaMapas.currentItem()->text();
        std::string party = partida.toStdString();
        for (size_t i = 0; i < party.length(); i++) {
            if (party.at(i) != '-') {
                name.push_back(party.at(i));
            } else {
                break;
            }
        }
    }
    return name;
}

void SalaCrear::enviarCrearPartida(QString cantJug, QString nameParty,
                                   QString nameMapa) {
    this->protocolo->sendCrear(this->house, cantJug.toInt(),
                               nameParty.toStdString(),
                               nameMapa.toStdString());
    if (!this->protocolo->receiveRet()) {
        this->menuAnterior->hide();
        this->hide();
        this->jugando = true;
        QApplication::quit();
    } else {
        this->mostrarMensajeDeExito("Creacion fallida");
    }
}

void SalaCrear::recibirProtocolo(ClientProtocol *protoc) {
    this->protocolo = protoc;
}

bool SalaCrear::estaJugando() {
    return this->jugando;
}


int SalaCrear::obtenerHouse() {
    return this->house;
}

void SalaCrear::establecerConexion() {
    this->conectado = true;
    this->recibirListadoMapas();
    this->mostrarListaDeMapas();
}

void SalaCrear::mostrarMensajeDeExito(QString mensaje) {
    QMessageBox::information(this, "Information", mensaje,
                             QMessageBox::Close);
}

void SalaCrear::recibirListadoMapas() {
    this->protocolo->sendListarMapas();
    this->listadoMapas = this->protocolo->receiveListadoMapas();
}

void SalaCrear::mostrarListaDeMapas() {
    this->listaMapas.clear();
    for (const std::pair<std::string, int> mapa: listadoMapas) {
        if (comCantidad.currentText().toInt() <= mapa.second)
            this->listaMapas.addItem(
                    QString::fromStdString(mapa.first + "-[Hasta " + std::to_string(mapa.second).data()) +
                    " Jugadores]");
    }
}

void SalaCrear::seleccionarCasa() {
    this->house = this->checkGroup.checkedId();
}

void SalaCrear::closeEvent(QCloseEvent *event) {
    this->salir = true; 
}

bool SalaCrear::quieroSalir() {
    return this->salir;
}

SalaCrear::~SalaCrear() {
}
