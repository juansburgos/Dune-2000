#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QtWidgets>
#include <map>
#include <vector>

#define WORMS 800
#define INIT_BASE 801
#define TILE_ROCK 572
#define TILE_SAND 48
#define ZERO_SPECIA 0

class MapWidget : public QWidget{
    public:
        explicit MapWidget(int imageSize, QWidget *parent = 0);
        virtual ~MapWidget();

        void clear();
        void cambiarSizeMap(int sizeMap);
        std::vector<std::vector<int>> obtenerListaTiles();
        std::vector<std::pair<int, int>> obtenerListaBuilds();
        std::vector<std::vector<int>> obtenerListaSpecias();
        std::vector<std::pair<int, int>> obtenerListaWorms();
        int pieceSize() const;
        int imageSize() const;
        void cargarTrozoMapa(QPixmap trozo, QPoint coordenada, int codigo);
        void cargarBuildMapa(QPixmap trozo, QPoint coordenada, int codigo);
        void cargarWormsMapa(QPixmap trozo, QPoint coordenada, int codigo);
        void cargarSpeciaMapa(QPixmap trozo, QPoint coordenada, int codigo);

    protected:
        void dragEnterEvent(QDragEnterEvent *event) override;
        void dragLeaveEvent(QDragLeaveEvent *event) override;
        void dragMoveEvent(QDragMoveEvent *event) override;
        void dropEvent(QDropEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void paintEvent(QPaintEvent *event) override;

    private:
        struct Piece {
            QPixmap pixmap;
            QRect rect;
            QPoint location;
            int codigo;
        };
        std::map<int,int> speciasTiles = {
            //300 301 320 321 mucha especia = 2
            // 748 799 poca especia = 1 
            {300, 2,}, {301, 2,}, {320, 2,}, {321, 2,}, {748, 1,}, {749, 1,},
            {750, 1,}, {751, 1,}, {752, 1,}, {753, 1,}, {754, 1,}, {755, 1,},
            {756, 1,}, {757, 1,}, {760, 1,}, {761, 1,}, {762, 1,}, {763, 1,},
            {764, 1,}, {765, 1,}, {766, 1,}, {767, 1,}, {768, 1,}, {769, 1,},
            {770, 1,}, {771, 1,}, {772, 1,}, {773, 1,}, {774, 1,}, {775, 1,},
            {776, 1,}, {777, 1,}, {778, 1,}, {779, 1,}, {780, 1,}, {781, 1,},
            {782, 1,}, {783, 1,}, {784, 1,}, {785, 1,}, {786, 1,}, {787, 1,},
            {788, 1,}, {789, 1,}, {790, 1,}, {791, 1,}, {792, 1,}, {793, 1,},
            {794, 1,}, {795, 1,}, {796, 1,}, {797, 1,}, {798, 1,}, {799, 1,}
        };
        int findPiece(const QRect &pieceRect) const;
        const QRect targetSquare(const QPoint &position) const;
        QList<Piece> pieces;
        QRect highlightedRect;
        int nImageSize;
        std::vector<std::vector<int>> listTiles;
        std::vector<std::pair<int, int>> listBuilds;
        std::vector<std::vector<int>> listSpecia;
        std::vector<std::pair<int,int>> listWorms;
        // Metodos privados
        bool agregarCodigoAListas(int codigo, int x, int y);
        void eliminarEdificio(int x, int y);
        void eliminarWorm(int x, int y);
        void cargarTrozo(QPixmap trozo, QPoint coordenada, int codigo);

};

#endif
