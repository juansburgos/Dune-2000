#include "mapWidget.h"
#include "common/defines.h"
#include <cstddef>
#include <utility>
#include <vector>

MapWidget::MapWidget(int imageSize, QWidget *parent) : QWidget(parent),
            nImageSize(imageSize) {
    setAcceptDrops(true);
}

void MapWidget::cambiarSizeMap(int sizeMap) {
    this->nImageSize = sizeMap;
    resize(sizeMap, sizeMap);
    this->clear();
}

void MapWidget::clear() {
    pieces.clear();
    highlightedRect = QRect();
    this->listTiles.clear();
    this->listTiles.resize(nImageSize / CELL_SIZE,
                        std::vector<int>(nImageSize / CELL_SIZE, TILE_SAND));
    this->listSpecia.clear();
    this->listSpecia.resize(nImageSize / CELL_SIZE, 
                        std::vector<int>(nImageSize / CELL_SIZE, ZERO_SPECIA));
    this->listBuilds.clear();
    this->listWorms.clear();
    update();
}

// cppcheck-suppress [unusedFunction]
void MapWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("image/x-map-piece"))
        event->accept();
    else
        event->ignore();
}

// cppcheck-suppress [unusedFunction]
void MapWidget::dragLeaveEvent(QDragLeaveEvent *event) {
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

// cppcheck-suppress [unusedFunction]
void MapWidget::dragMoveEvent(QDragMoveEvent *event) {
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));
    if (event->mimeData()->hasFormat("image/x-map-piece")
        && findPiece(targetSquare(event->pos())) == -1) {
            highlightedRect = targetSquare(event->pos());
            event->setDropAction(Qt::MoveAction);
            event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
    update(updateRect);
}

// cppcheck-suppress [unusedFunction]
void MapWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("image/x-map-piece") &&
        findPiece(targetSquare(event->pos())) == -1) {
            QByteArray pieceData = event->mimeData()->data("image/x-map-piece");
            QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
            Piece piece;
            piece.rect = targetSquare(event->pos());
            dataStream >> piece.pixmap >> piece.location >> piece.codigo;
            int codigo = piece.codigo;
            if (agregarCodigoAListas(codigo, piece.rect.y(), piece.rect.x())) {
                pieces.append(piece);
                highlightedRect = QRect();
                update(piece.rect);
                event->setDropAction(Qt::MoveAction);
                event->accept();
            } else {
                highlightedRect = QRect();
                event->ignore();
            }
    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

bool MapWidget::agregarCodigoAListas(int codigo, int x, int y) {
    if (codigo == INIT_BASE) {
        int posX = x / CELL_SIZE;
        int posY = y / CELL_SIZE;
        int tam = nImageSize / CELL_SIZE;
        if (posX  + 4 <= tam && posY + 4 <= tam) {
            listBuilds.push_back({y, x});
            codigo = TILE_ROCK;
        } else {
            QMessageBox::information(this, "Error",
                        "No se puede agregar el edificio en esta posicion",
                        QMessageBox::Close);
            return false;
        }
    } else if (speciasTiles.count(codigo)) {
        listSpecia.at(x / CELL_SIZE).at(y / CELL_SIZE) = speciasTiles[codigo];
    } else if (codigo == WORMS) {
        listWorms.push_back({y, x});
        codigo = TILE_SAND;
    }
    listTiles.at(x / CELL_SIZE).at(y / CELL_SIZE) = codigo;
    return true;
}

int MapWidget::findPiece(const QRect &pieceRect) const {
    for (int i = 0, size = pieces.size(); i < size; i++) {
        if (pieces.at(i).rect == pieceRect)
            return i;
    }
    return -1;
}

void MapWidget::eliminarEdificio(int x, int y) {
    for (size_t i = 0; i < listBuilds.size(); i++) {
        std::pair<int, int> build = listBuilds.at(i);
        if (build.first == y && build.second == x) {
            listBuilds.erase(listBuilds.begin() + i);
        }
    }
}

// cppcheck-suppress [unusedFunction]
void MapWidget::mousePressEvent(QMouseEvent *event) {
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);
    if (found == -1)
        return;
    Piece piece = pieces.takeAt(found);        
    update(square);
    if (piece.codigo == INIT_BASE) {
        this->eliminarEdificio(piece.rect.y(),
                                piece.rect.x());
    } else if (speciasTiles.count(piece.codigo)) {
        listSpecia.at(piece.rect.y() / CELL_SIZE).at(
                        piece.rect.x() / CELL_SIZE) = ZERO_SPECIA;
    } else if (piece.codigo == WORMS) {
        this->eliminarWorm(piece.rect.y(),
                            piece.rect.x());
    }
    listTiles.at(piece.rect.y()/CELL_SIZE).at(piece.rect.x()/CELL_SIZE) = TILE_SAND; 
}

void MapWidget::eliminarWorm(int x, int y) {
    for (size_t i = 0; i < obtenerListaWorms().size(); i++) {
        std::pair<int, int> worms = listWorms.at(i);
        if (worms.first == y && worms.second == x) {
            listWorms.erase(listWorms.begin() + i);
        }
    }
}

// cppcheck-suppress [unusedFunction]
void MapWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::black);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (const Piece &piece : pieces)
        painter.drawPixmap(piece.rect, piece.pixmap);
}

const QRect MapWidget::targetSquare(const QPoint &position) const {
    QPoint topLeft = QPoint(position.x() / pieceSize(), position.y() / pieceSize()) * pieceSize();
    return QRect(topLeft, QSize(pieceSize(), pieceSize()));
}

int MapWidget::pieceSize() const {
    return CELL_SIZE;
}

int MapWidget::imageSize() const {
    return nImageSize;
}

std::vector<std::vector<int>> MapWidget::obtenerListaTiles() {
    return this->listTiles;
}

std::vector<std::pair<int, int>> MapWidget::obtenerListaBuilds() {
    return this->listBuilds;
}

std::vector<std::vector<int>> MapWidget::obtenerListaSpecias() {
    return this->listSpecia;
}

std::vector<std::pair<int, int>> MapWidget::obtenerListaWorms() {
    return this->listWorms;
}

void MapWidget::cargarTrozoMapa(QPixmap trozo, QPoint coordenada, int codigo) {
    this->cargarTrozo(trozo, coordenada, codigo);
    listTiles.at(coordenada.y()).at(coordenada.x()) = codigo;
}

void MapWidget::cargarBuildMapa(QPixmap trozo, QPoint coordenada, int codigo) {
    this->cargarTrozo(trozo, coordenada, codigo);
    listBuilds.push_back({coordenada.x()*CELL_SIZE,coordenada.y()*CELL_SIZE});
}

void MapWidget::cargarWormsMapa(QPixmap trozo, QPoint coordenada, int codigo) {
    this->cargarTrozo(trozo, coordenada, codigo);
    listWorms.push_back({coordenada.x()*CELL_SIZE, coordenada.y()*CELL_SIZE});
}

void MapWidget::cargarSpeciaMapa(QPixmap trozo, QPoint coordenada, int codigo) {
    this->cargarTrozo(trozo, coordenada, codigo);
    listSpecia.at(coordenada.y()).at(coordenada.x()) = codigo;
}

void MapWidget::cargarTrozo(QPixmap trozo, QPoint coordenada, int codigo) {
    Piece piece;
    piece.pixmap = trozo;
    QPoint topLeft = QPoint(coordenada.x(), coordenada.y()) * pieceSize();
    piece.rect = QRect(topLeft, QSize(pieceSize(), pieceSize()));
    piece.codigo = codigo;
    pieces.append(piece);
}

MapWidget::~MapWidget(){
}
