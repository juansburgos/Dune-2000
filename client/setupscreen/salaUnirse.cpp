#include "salaUnirse.h"

SalaUnirse::SalaUnirse(QWidget *parent) : QWidget(parent),
    namePartida("Partida: ", this),
    partidaLabel(" ", this), checkAtrei(this), checkHarko(this),
    checkOrdos(this), checkGroup(this), labelAtrei("Atreides"),
    labelHarko("Harkonnen", this), labelOrdos("Ordos", this),
    buttonAtras("Atras", this), buttonUnirse("Unirse", this),
    gridUnirse(this), house(-1), jugando(false), salir(false) {
    
    this->iniciarWidget();
    QHBoxLayout *hLayoutName = new QHBoxLayout;
    hLayoutName->addWidget(&namePartida, Qt::AlignCenter);
    hLayoutName->addWidget(&partidaLabel, Qt::AlignCenter);
    
    // Selecciono Casa
    checkAtrei.setObjectName("Atreides");
    checkAtrei.setChecked(true);
    checkHarko.setObjectName("Harkonnen");
    checkHarko.setChecked(false);
    checkOrdos.setObjectName("Ordos");
    checkOrdos.setChecked(false);
    checkGroup.addButton(&checkAtrei,1);
    checkGroup.addButton(&checkHarko,0);
    checkGroup.addButton(&checkOrdos,2);

    QHBoxLayout *checkLayout = new QHBoxLayout;
    checkLayout->addWidget(&checkAtrei);
    checkLayout->addWidget(&checkHarko);
    checkLayout->addWidget(&checkOrdos);

    QHBoxLayout *labelCheck = new QHBoxLayout;
    labelCheck->addWidget(&labelAtrei);
    labelCheck->addWidget(&labelHarko);
    labelCheck->addWidget(&labelOrdos);
    
    QVBoxLayout *layoutGroup = new QVBoxLayout;
    layoutGroup->addLayout(checkLayout);
    layoutGroup->addLayout(labelCheck);

    QGroupBox *casaBox = new QGroupBox;    
    casaBox->setLayout(layoutGroup);
    casaBox->setTitle("Selecciona tu Casa");

    // crear y atras
    QHBoxLayout *finalLayout = new QHBoxLayout;
    finalLayout->addWidget(&buttonAtras);
    finalLayout->addWidget(&buttonUnirse);
    
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &SalaUnirse::volverAMultiplayer);
    connect(&buttonUnirse, &QAbstractButton::clicked, this,
           &SalaUnirse::unirseAPartida);
    
    // Presentacion de pantalla Crear
    gridUnirse.addLayout(hLayoutName, 0, 0, Qt::AlignTop);
    gridUnirse.addWidget(casaBox, 2, 0, Qt::AlignHCenter);
    gridUnirse.addLayout(finalLayout, 3, 0, Qt::AlignCenter);
    this->setLayout(&gridUnirse); 
}

void SalaUnirse::unirseAPartida() {
    this->seleccionarCasa();
    if (house >= 0) {
        this->protocolo->sendUnirse(this->house,
                        partidaLabel.text().toStdString());
        if (!this->protocolo->receiveRet()) {
            this->hide();
            this->jugando = true;
            QApplication::quit();
        } else {
            this->mostrarMensajeDeExito("Union fallida");
        }
    }
}

void SalaUnirse::mostrarMensajeDeExito(QString mensaje) {
    QMessageBox::information(this, "Information", mensaje,
                            QMessageBox::Close); 
}

void SalaUnirse::recibirConexion(ClientProtocol *protocol) {
    this->protocolo = protocol;
}

void SalaUnirse::asignarNombreDePartida(QString nombre) {
    this->partidaLabel.setText(nombre);
}

bool SalaUnirse::estaJugando() {
    return this->jugando;
}

void SalaUnirse::asignarMenuAnterior(QWidget *menuAnte) {
    this->menuAnterior = menuAnte;
}

void SalaUnirse::volverAMultiplayer() {
    this->menuAnterior->show();
    this->hide();
    this->asignarMenuAnterior(nullptr);
}

void SalaUnirse::iniciarWidget() {
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

void SalaUnirse::seleccionarCasa() {
    this->house = checkGroup.checkedId();
}

int SalaUnirse::obtenerHouse() {
    return this->house;
}

SalaUnirse::~SalaUnirse() {
}

void SalaUnirse::closeEvent(QCloseEvent *event) {
    this->salir = true;
}

bool SalaUnirse::quieroSalir() {
    return this->salir;
}
