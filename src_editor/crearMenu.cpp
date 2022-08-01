#include "crearMenu.h"
#include "common/defines.h"
#include "createFileMap.h"
#include <algorithm>
#include <fstream>
#include <utility>
#include <map>
#include <vector>

CrearMenu::CrearMenu(QWidget *parent) : QWidget(parent),
            nameMenu("Crea tu Mapa", this), buttonAtras("Atras", this),
            buttonCrear("Crear", this), mainMenu(nullptr), mainLayout(this),
            mapaACrear(), trozosMapaList(this), mapaWidget(0),
            labelTam("Ingrese tamanio del Mapa: ", this), tamMap(this),
            buttonTamMap("Cambiar Tamanio", this),
            // labelTiles("Seleccione Terreno", this),
            buttonClean("Limpiar Mapa", this), // comboTiles(this),
            labelName("Nombre del Mapa", this), lineName(this) {
    this->iniciarWidget();
    trozosMap = new PiecesMap(CELL_SIZE, this);
    this->mostrarListaDeTiles();
    this->loadImage();
    
    QHBoxLayout *layoutName = new QHBoxLayout;
    layoutName->setAlignment(Qt::AlignCenter);
    nameMenu.setMargin(5);
    layoutName->addWidget(&nameMenu);

    // QHBoxLayout *layoutTiles = new QHBoxLayout;
    // comboTiles.setMinimumWidth(120);
    // layoutTiles->addWidget(&labelTiles);
    // layoutTiles->addWidget(&comboTiles);

    QHBoxLayout *layoutTamanio = new QHBoxLayout;
    layoutTamanio->setSpacing(10);
    layoutTamanio->addWidget(&labelTam);
    layoutTamanio->addWidget(&tamMap);
    layoutTamanio->addWidget(&buttonTamMap);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(15);
    // layout->addLayout(layoutTiles);
    layout->addLayout(layoutTamanio);

    QHBoxLayout *layoutNameMap = new QHBoxLayout;
    layoutNameMap->addWidget(&labelName);
    layoutNameMap->addWidget(&lineName);

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

    // trozosMapaList.setModel(trozosMap);
    QVBoxLayout *layoutImagen = new QVBoxLayout;
    layoutImagen->addWidget(&trozosMapaList);
    layoutImagen->addWidget(&buttonClean);

    QScrollArea *scrollMapa = new QScrollArea(this);
    scrollMapa->setWidget(&mapaWidget);
    frameLayout->addLayout(layoutImagen);
    frameLayout->addWidget(scrollMapa);

    QHBoxLayout *layoutButton = new QHBoxLayout;
    layoutButton->setAlignment(Qt::AlignCenter);
    layoutButton->addWidget(&buttonAtras);
    layoutButton->addWidget(&buttonCrear);

    mainLayout.setSpacing(20);
    mainLayout.addLayout(layoutName, 0, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutNameMap, 1, 0, Qt::AlignCenter);
    mainLayout.addLayout(layout, 2, 0, Qt::AlignCenter);
    mainLayout.addLayout(frameLayout, 3, 0, Qt::AlignCenter);
    mainLayout.addLayout(layoutButton, 4, 0, Qt::AlignCenter);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(&buttonClean, &QAbstractButton::clicked, this,
            &CrearMenu::limpiarMapa);
    connect(&buttonTamMap, &QAbstractButton::clicked, this,
            &CrearMenu::cambiarSizeMap);
    connect(&buttonCrear, &QAbstractButton::clicked, this,
            &CrearMenu::guardarMapa);
    connect(&buttonAtras, &QAbstractButton::clicked, this,
            &CrearMenu::volverAlMain);
    // connect(&comboTiles, &QComboBox::currentTextChanged, this,
    //         &CrearMenu::loadImage);
    this->setLayout(&mainLayout);
}

void CrearMenu::mostrarListaDeTiles() {
    QDir directorio("../assets/tiles/terrain/");
    QStringList filter;
    filter << "*.jpeg" << "*.jpg" << "*.png" << "*.bmp";
    directorio.setNameFilters(filter);
    QStringList lista = directorio.entryList();
    // for(QString file: lista){
    //     comboTiles.addItem(file);
    // }
}

void CrearMenu::limpiar() {
    this->mapaWidget.cambiarSizeMap(0);
    this->lineName.clear();
    this->tamMap.clear();
    // this->comboTiles.setCurrentIndex(0);
    this->loadImage();
    this->trozosMapaList.setModel(nullptr);
}

void CrearMenu::guardarMapa() {
    std::string mapaName = lineName.text().toStdString();
    if (!mapaName.empty()) {
        std::vector<std::pair<int, int>> builds = mapaWidget.obtenerListaBuilds();
        if (builds.empty()) {
            this->mostrarMensaje("Dibuje la posicion de un Jugador");
            return;
        }
        std::vector<std::pair<int, int>> worm = mapaWidget.obtenerListaWorms();
        if (worm.empty()) {
            this->mostrarMensaje("Dibuje la posicion del Worm");
            return;
        }
        std::string nameFile = "../maps/" + mapaName + ".yaml";
        CreateFileMap map(this->mapaWidget.obtenerListaTiles(),
                        this->mapaWidget.obtenerListaSpecias(), builds,
                        worm, 
                        //comboTiles.currentText().toStdString()
                        "BLOXBGBS.bmp");
        std::fstream mapa(nameFile, std::ios_base::out);
        mapa << map.crearMapYAML();
        mapa.close();
        this->mostrarMensaje("Mapa guardado");
    } else {
        this->mostrarMensaje("Ingrese nombre del Mapa");
    }
}

void CrearMenu::mostrarMensaje(QString mensaje) {
    QMessageBox::information(this, "Information", mensaje,
                            QMessageBox::Close); 
}

void CrearMenu::limpiarMapa() {
    this->mapaWidget.clear();
}

void CrearMenu::cambiarSizeMap() {
    int size = this->tamMap.text().toInt() * CELL_SIZE;
    this->mapaWidget.cambiarSizeMap(size);
    QPixmap trozo = this->trozosMap->getPiece(TILE_SAND);
    for (int i = 0; i < size /  CELL_SIZE; i++) {
        for (int j = 0; j < size / CELL_SIZE; j++) {
            this->mapaWidget.cargarTrozoMapa(trozo,QPoint(j, i), TILE_SAND);
        }
    }
    this->trozosMapaList.setModel(this->trozosMap);
}

void CrearMenu::loadImage() {
    this->trozosMap->clear();
    QPixmap newImage;
    // QString file = comboTiles.currentText();
    if (!newImage.load("../assets/tiles/terrain/BLOXBGBS.bmp"))
        return;
    mapaACrear = newImage;
    this->setupMapa();
    // trozosMapaList.setModel(trozosMap);
}

void CrearMenu::setupMapa() {
    for (int i = 0; i < mapaACrear.height()/CELL_SIZE; i++) {
        for (int j = 0; j < mapaACrear.width()/CELL_SIZE; j++) {
            QPixmap recorte = mapaACrear.copy(j*CELL_SIZE, i*CELL_SIZE,
                                CELL_SIZE, CELL_SIZE);
            trozosMap->addPiece(recorte, QPoint(i, j));
        }
    }
    this->agregarTilesBase();
    // mapaWidget.clear();
    // this->cambiarSizeMap();
}

void CrearMenu::agregarTilesBase() {
    QPixmap tileBase("../assets/tiles/tileBase.jpeg");
    for (int i = 0; i < tileBase.height() / CELL_SIZE; i++) {
        for (int j = 2; j < (tileBase.width() / CELL_SIZE) - 1; j++) {
            QPixmap recorte = tileBase.copy(j*CELL_SIZE, i*CELL_SIZE,
                                CELL_SIZE, CELL_SIZE);
            trozosMap->addPiece(recorte, QPoint(800+i,800+j));
        }
    }
}

void CrearMenu::asignarMainMenu(QWidget *main) {
    this->mainMenu = main;
}

void CrearMenu::volverAlMain() {
    this->mainMenu->show();
    this->hide();
    this->asignarMainMenu(nullptr);
}

void CrearMenu::iniciarWidget() {
    this->setWindowTitle("EDITOR DUNE 2000");
    this->setObjectName("Crear");
    QFontDatabase::addApplicationFont("../assets/font/Dune2k.ttf");
    QFont font("Dune2k");
    this->setFont(font);
    QFile file(QString("../assets/css/editor.qss"));
    file.open(QFile::ReadOnly);
    this->setStyleSheet(file.readAll());
}

CrearMenu::~CrearMenu() {
}
