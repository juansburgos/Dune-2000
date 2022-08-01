#ifndef PLAYERREPRODUCTOR_H
#define PLAYERREPRODUCTOR_H

#include <QtWidgets>
#include <QtMultimedia>

class PlayerReproductor : public QWidget {
public:
    explicit PlayerReproductor(QWidget *parent = 0);
    virtual ~PlayerReproductor();
    void next();

private:
    QMediaPlaylist playList;
    QMediaPlayer player;

};

#endif