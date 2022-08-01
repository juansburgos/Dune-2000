#include "piecesMap.h"
#include <iostream>

PiecesMap::PiecesMap(int pieceSize, QObject *parent) : 
        QAbstractListModel(parent), nPieceSize(pieceSize) {
}

QVariant PiecesMap::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DecorationRole)
        return QIcon(pixmaps.value(index.row()).scaled(nPieceSize,nPieceSize,
                    Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else if (role == Qt::UserRole)
        return pixmaps.value(index.row());
    else if (role == Qt::UserRole + 1)
        return locations.value(index.row());

    return QVariant();
}

void PiecesMap::addPiece(const QPixmap &pixmap, const QPoint &location) {
    int row = pixmaps.size();
    beginInsertRows(QModelIndex(), row, row);
    pixmaps.insert(row, pixmap);
    locations.insert(row, location);
    endInsertRows();
}

Qt::ItemFlags PiecesMap::flags(const QModelIndex &index) const {
    if (index.isValid())
        return (QAbstractListModel::flags(index) | Qt::ItemIsDragEnabled);
    return Qt::ItemIsDropEnabled;
}

// cppcheck-suppress [unusedFunction]
QStringList PiecesMap::mimeTypes() const {
    QStringList types;
    types << "image/x-map-piece";
    return types;
}

QMimeData* PiecesMap::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    for (const QModelIndex &index : indexes) {
        if (index.isValid()) {
            QPixmap pixmap = qvariant_cast<QPixmap>(data(index, Qt::UserRole));
            QPoint location = data(index, Qt::UserRole + 1).toPoint();
            stream << pixmap << location << index.row();
        }
    }
    mimeData->setData("image/x-map-piece", encodedData);
    return mimeData;
}

// cppcheck-suppress [unusedFunction]
bool PiecesMap::dropMimeData(const QMimeData *data, Qt::DropAction action,
                    int row, int column, const QModelIndex &parent) {
    if (!data->hasFormat("image/x-map-piece"))
        return false;
    if (action == Qt::IgnoreAction)
        return true;
    if (column > 0)
        return false;
    int endRow;

    if (!parent.isValid()) {
        if (row < 0)
            endRow =pixmaps.size();
        else
            endRow = qMin(row, pixmaps.size());
    } else {
        endRow = parent.row();
    }
    
    QByteArray encodedData = data->data("image/x-map-piece");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);

    while (!stream.atEnd()) {
        QPixmap pixmap;
        QPoint location;
        stream >> pixmap >> location;

        beginInsertRows(QModelIndex(), endRow, endRow);
        pixmaps.insert(endRow, pixmap);
        locations.insert(endRow, location);
        endInsertRows();
        ++endRow;
    }

    return true;
}

// cppcheck-suppress [unusedFunction]
int PiecesMap::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : pixmaps.size();
}

// cppcheck-suppress [unusedFunction]
Qt::DropActions PiecesMap::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}

QPixmap PiecesMap::getPiece(int i) {
    return pixmaps.at(i);
}

void PiecesMap::clear() {
    if (!pixmaps.isEmpty()) {
        pixmaps.clear();
        locations.clear();
    }
}

PiecesMap::~PiecesMap() {
}