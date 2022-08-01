#include "editarMenu.h"
#include "common/defines.h"
#include "createFileMap.h"
#include "src_editor/mapWidget.h"
#include <algorithm>
#include <fstream>
#include <map>
#include <qdebug.h>
#include <qpixmap.h>
#include <vector>

EditarMenu::EditarMenu(QWidget *parent) : QWidget(parent),
            nameMenu("Edita tu Mapa", this), buttonAtras("Atras", this),
            buttonEditar("Editar", this), mainMenu(nullptr), mainLayout(this),
            mapaACrear(), trozosMapaList(this), mapaWidget(0),
            buttonOpen("Abrir Archivo", this), nameTerrain() {
    this->iniciarWidget();
    trozosMap = new PiecesMap(CELL_SIZE, this);
    
    QHBoxLayout *layoutName = new QHBoxLayout;
    layoutName->setAlignment(Qt::AlignCenter);
    nameMenu.setMargin(5);
    layoutName->addWidget(&nameMenu);

    QHBoxLayout *layoutAbrir = new QHBoxLayout;
    layoutAbrir->addWidget(&buttonOpen);

    QHBoxLayout *frameLayout = new QHBoxLayout;
    trozosMapaList.setObjectName("Trozos");
    trozosMapaList.setMaximumWidth(670);
    trozosMapaList.setDragEnabled(true);
    trozosMapaList.setViewMode(QListView::IconMode);
    trozosMapaList.setIconSize(QSize(CELL_SIZE, CELL_SIZE));
    trozosMapaList.setGridSize(QSize(32, 32));
    trozosMapaList.setSpacing(0);
    trozosMapaList.setMovement(QListView::Snap);
    trozosMapaList.setAcceptDrops(false);

    QVBoxLayout *layoutImagen = new QVBoxLayout;
    layoutImagen->addWidget(&trozosMapaList);

    QScrollArea *scrollMapa = new QScrollArea(this);
    scrollMapa->setWidget(&mapaWidget);
    frameLayout->addLayout(layoutImagen);
    frameLayout->addWidget(scrollMapa);

    QHBoxLayout *layoutButton = new QHBoxLayout;
    layoutButton->setAlignment(Qt::AlignCenter);
    layoutButton->addWidget(&buttonAtras);
    layoutButton->addWidget(&buttonEditar);

    mainLayout.setSpacing(20);
    mainLayout.addLayout(layoutName, 0, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutAbrir, 1, 0, Qt::AlignCenter);
    mainLayout.addLayout(frameLayout, 2, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutButton, 3, 0, Qt::AlignCenter);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    connect(&buttonOpen, &QAbstractButton::clicked, this,
            &EditarMenu::abrirArchivo);
    connect(&buttonEditar, &QAbstractButton::clicked, this,
            &EditarMenu::editarMapa);
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &EditarMenu::volverAlMain);
    this->setLayout(&mainLayout);
}

void EditarMenu::iniciarWidget() {
    this->setWindowTitle("EDITOR DUNE 2000");
    this->setObjectName("Editar");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/editor.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

void EditarMenu::limpiar() {
    this->mapaWidget.clear();
    this->mapaWidget.cambiarSizeMap(0);
    this->trozosMap->clear();
}

void EditarMenu::loadImage() {
    this->trozosMap->clear();
    QPixmap newImage;
    QString name(nameTerrain.data());
    if (!newImage.load("../assets/tiles/terrain/" + name))
        return;
    mapaACrear = newImage;
    this->setupMapa();
}

void EditarMenu::setupMapa() {
    for (int i = 0; i < mapaACrear.height()/CELL_SIZE; i++) {
        for (int j = 0; j < mapaACrear.width()/CELL_SIZE; j++) {
            QPixmap recorte = mapaACrear.copy(j*CELL_SIZE, i*CELL_SIZE,
                                CELL_SIZE, CELL_SIZE);
            trozosMap->addPiece(recorte, QPoint(i, j));
        }
    }
    this->agregarTilesBase();
}

void EditarMenu::agregarTilesBase() {
    QPixmap tileBase("../assets/tiles/tileBase.jpeg");
    for (int i = 0; i < tileBase.height() / CELL_SIZE; i++) {
        for (int j = 2; j < (tileBase.width() / CELL_SIZE) - 1; j++) {
            QPixmap recorte = tileBase.copy(j*CELL_SIZE, i*CELL_SIZE,
                                CELL_SIZE, CELL_SIZE);
            trozosMap->addPiece(recorte, QPoint(800+i,800+j));
        }
    }
}

void EditarMenu::asignarMainMenu(QWidget *main) {
    this->mainMenu = main;
}

void EditarMenu::volverAlMain() {
    this->mainMenu->show();
    this->hide();
    this->asignarMainMenu(nullptr);
}

void EditarMenu::abrirArchivo() {
    const QString directorio = "../maps/";
    QFileDialog dialog(this, "Open Map", directorio);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.selectMimeTypeFilter("YAML/yaml");
    if (dialog.exec() == QDialog::Accepted) {
        this->nameFile = dialog.selectedFiles().constFirst();
        this->map = YAML::LoadFile(nameFile.toStdString());
        this->cargarTrozosDeTerreno();
        this->cargarMapa();
        return;   
    }
}

void EditarMenu::cargarTrozosDeTerreno() {
    this->nameTerrain = "BLOXBGBS.bmp"; // this->map["terrain"].as<std::string>();
    this->loadImage();
    trozosMapaList.setModel(trozosMap);
}

void EditarMenu::cargarMapa() {
    this->mapaWidget.cambiarSizeMap(this->map["tiles"][0].size()*CELL_SIZE);
    for (int i = 0; i < this->map["tiles"].size(); i++) {
        std::vector<int> aux = map["tiles"][i].as<std::vector<int>>();
        for (int j = 0; j < aux.size(); j++) {
            int codigo = aux[j];
            QPixmap trozo = this->trozosMap->getPiece(codigo);
            this->mapaWidget.cargarTrozoMapa(trozo,QPoint(j, i), codigo);
        }
    }

    for (int i = 0; i < this->map["specia"].size(); i++) {
        std::vector<int> aux = map["specia"][i].as<std::vector<int>>();
        for (int j = 0; j < aux.size(); j++) {
            int codigo = aux[j];
            QPixmap trozo;
            if (codigo == 0)
                continue;
            if (codigo == 1)
                trozo = this->trozosMap->getPiece(748);
            if (codigo == 2)
                trozo = this->trozosMap->getPiece(301);
            this->mapaWidget.cargarSpeciaMapa(trozo, QPoint(j, i), codigo);
        }
    }

    for (int i = 0; i < this->map["players"].size(); i++) {
        std::vector<int> aux = map["players"][i].as<std::vector<int>>();
        QPixmap trozo = this->trozosMap->getPiece(INIT_BASE);
        this->mapaWidget.cargarBuildMapa(trozo,
                QPoint(aux[0] / CELL_SIZE,
                                                aux[1] / CELL_SIZE),
                                                INIT_BASE);
    }

    YAML::Node lineup = map["worms"];
    for(YAML::const_iterator it=lineup.begin();it!=lineup.end();++it) {
        int x = it->second.as<int>();
        int y = it->first.as<int>();
        QPixmap trozo = this->trozosMap->getPiece(WORMS);
        this->mapaWidget.cargarWormsMapa(trozo, QPoint(y / CELL_SIZE,
                                                x / CELL_SIZE), WORMS);
    }
}

void EditarMenu::editarMapa() {
    std::vector<std::pair<int, int>> builds = this->mapaWidget.obtenerListaBuilds();
    if (builds.empty()) {
        this->mostrarMensaje("Dibuje la posicion de almenos un Jugador");
        return;
    }
    std::vector<std::pair<int, int>> worm = mapaWidget.obtenerListaWorms();
    if (worm.empty()) {
        this->mostrarMensaje("Dibuje la posicion del Worm");
        return;
    }
    CreateFileMap mapFile(this->mapaWidget.obtenerListaTiles(),
                        this->mapaWidget.obtenerListaSpecias(), builds,
                        worm, this->nameTerrain);  
    std::fstream mapa(nameFile.toStdString(), std::ios_base::out);
    mapa << mapFile.crearMapYAML();
    mapa.close();
    this->mostrarMensaje("Mapa guardado");
}

void EditarMenu::mostrarMensaje(QString mensaje) {
    QMessageBox::information(this, "Information", mensaje,
                            QMessageBox::Close); 
}

EditarMenu::~EditarMenu(){
}
