#include "playerReproductor.h"

PlayerReproductor::PlayerReproductor(QWidget *parent) : QWidget(parent),
    playList(this), player() {
    QDir directorio(QDir::currentPath());
    directorio.cd("../assets/audio/music/");
    directorio.setNameFilters(QStringList({"*.mp3"}));
    QStringList lista = directorio.entryList();
    for(QString file: lista){
        QString path = directorio.path() + "/" + file;
        this->playList.addMedia(QUrl::fromLocalFile(path));
    }
    this->playList.setCurrentIndex(1);
    this->playList.shuffle();
    this->player.setPlaylist(&this->playList);
    this->player.setVolume(15);
    this->player.play();
}

void PlayerReproductor::next() {
    this->playList.next();
}

PlayerReproductor::~PlayerReproductor() {
}
