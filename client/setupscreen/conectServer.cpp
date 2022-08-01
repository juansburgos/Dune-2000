#include "conectServer.h"
#include <qmessagebox.h>

conectServer::conectServer(QWidget *parent) : QWidget(parent),
    lineIp(this), linePuerto(this), vMainLayout(this), ipLabel("IP", this),
    puertoLabel("Puerto", this), buttonConect("Conectar", this),
    buttonAtras("Atras", this), menuAnterior(nullptr), conexion(false),
    salir(false) {

    this->iniciarWidget();
    lineIp.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lineIp.setPlaceholderText("xxx.xxx.xxx.xxx");
    lineIp.setText("localhost");
    ipLabel.setBuddy(&lineIp);
    linePuerto.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    linePuerto.setPlaceholderText("xxxx");
    linePuerto.setText("http-alt");
    puertoLabel.setBuddy(&linePuerto);
   
    QHBoxLayout *hLayoutIp = new QHBoxLayout;
    hLayoutIp->setSpacing(15);
    hLayoutIp->addWidget(&ipLabel);
    hLayoutIp->addWidget(&lineIp);
    
    QHBoxLayout *hLayoutPuerto = new QHBoxLayout;
    hLayoutPuerto->setSpacing(5);
    hLayoutPuerto->addWidget(&puertoLabel);
    hLayoutPuerto->addWidget(&linePuerto);
    
    QHBoxLayout *hButton = new QHBoxLayout;
    buttonConect.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonAtras.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    hButton->addWidget(&buttonConect, QDialogButtonBox::ActionRole);
    hButton->addWidget(&buttonAtras, QDialogButtonBox::ActionRole);

    vMainLayout.setAlignment(Qt::AlignCenter);
    vMainLayout.setSpacing(15);
    vMainLayout.addLayout(hLayoutIp, 0, 0, Qt::AlignCenter | Qt::AlignHCenter);
    vMainLayout.addLayout(hLayoutPuerto, 1, 0, Qt::AlignCenter);
    vMainLayout.addLayout(hButton, 2, 0, Qt::AlignCenter);

    connect(&buttonConect, &QAbstractButton::clicked, this,
                    &conectServer::conectar);
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &conectServer::irAMenuPrincipal);

    this->setLayout(&vMainLayout);
}

void conectServer::iniciarWidget() {
    this->setFixedSize(800, 600);
    this->setWindowTitle("DUNE 2000");
    this->setObjectName("Conectar");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/config.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

void conectServer::asignarMenuAnterior(QWidget *menuAnte) {
    this->menuAnterior = menuAnte;
}

void conectServer::irAMenuPrincipal() {
    this->menuAnterior->show();
    this->hide();
    this->asignarMenuAnterior(nullptr);
}
  
void conectServer::conectar() {
    QString ipString = this->lineIp.text();
    QString puertoString = this->linePuerto.text();
    if (!ipString.isEmpty() && !puertoString.isEmpty()) {
        this->ip = ipString.toStdString();
        this->puerto = puertoString.toStdString();
        this->conexion = true;
        this->hide();    
        QApplication::quit();
    } else {
        QMessageBox::information(this, "Error",
                "Complete los datos", QMessageBox::Close);        
    }
}

bool conectServer::establecerConexion() {
    return this->conexion;
}

std::string conectServer::getPuerto() {
    return this->puerto;
}

std::string conectServer::getIp() {
    return this->ip;
}

conectServer::~conectServer() {
}

// cppcheck-suppress [unusedFunction]
void conectServer::closeEvent(QCloseEvent *event) {
    this->salir = true;
}

bool conectServer::quieroSalir() {
    return this->salir;
}
