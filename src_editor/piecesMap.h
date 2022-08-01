#ifndef PIECESMAP_H
#define PIECESMAP_H

#include <QtWidgets>

class PiecesMap : public QAbstractListModel {
    public:
        explicit PiecesMap(int pieceSize, QObject *parent = 0);
        QVariant data(const QModelIndex &index,
                        int role = Qt::DisplayRole) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                    int column, const QModelIndex &parent) override;
        QMimeData* mimeData(const QModelIndexList &indexes)  const override;
        QStringList mimeTypes() const override;
        int rowCount(const QModelIndex &parent) const override;
        Qt::DropActions supportedDropActions() const override;

        void addPiece(const QPixmap &pixmap, const QPoint &location);
        QPixmap getPiece(int i);
        void clear();
        virtual ~PiecesMap();

    private:
        QList<QPoint> locations;
        QList<QPixmap> pixmaps;
        int nPieceSize;
};

#endif
