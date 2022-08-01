#include "SDLcam.h"

SDLcam::SDLcam(int maxX, int maxY, Partida &partida) : maxX(maxX), maxY(maxY), direccion(0) {
    for (auto &b : partida.getBuildings()) {
        if (b.playerID == partida.getPlayerID() && b.type == TYPE_CENTRO_CONSTRUCCION) {
            if (((b.position.first * ZOOM) - maxX) > SCROLL_FACTOR)
                x = ((b.position.first * ZOOM) - (maxX / 2)) / SCROLL_FACTOR;
            if (((b.position.second * ZOOM) - maxY) > SCROLL_FACTOR)
                y = ((b.position.second * ZOOM) - (maxY / 2)) / SCROLL_FACTOR;
        }
    }
}

int SDLcam::getX() {
    return x * SCROLL_FACTOR;
}

int SDLcam::getY() {
    return y * SCROLL_FACTOR;
}

void SDLcam::setDireccion(int dir) {
    direccion = dir;
}

bool SDLcam::isInside(std::pair<int, int> itemPosition) {
    return (itemPosition.first / ZOOM - getX()) < maxX &&
           (itemPosition.second / ZOOM - getY()) < maxY;
}

bool SDLcam::tileIsInside(std::pair<int, int> itemPosition) {
    return (itemPosition.first * CELL_SIZE * ZOOM - getX()) < maxX &&
           (itemPosition.second * CELL_SIZE * ZOOM - getY()) < maxY;
}

void SDLcam::updateWindow(int windowWidth, int windowHeight) {
    maxX = windowWidth;
    maxY = windowHeight;
}

float SDLcam::turnToViewSize(float size) {
    return size * ZOOM * CELL_SIZE;
}

std::pair<int, int> SDLcam::turnToViewSize(std::pair<int, int> cursor) {
    int posX = (cursor.first) + getX();
    int posY = (cursor.second) + getY();

    return std::pair<int, int>(posX, posY);
}

void SDLcam::setToViewSize(std::pair<int, int> &cursor) {
    cursor.first = cursor.first / ZOOM + x * SCROLL_FACTOR / ZOOM;
    cursor.second = cursor.second / ZOOM + y * SCROLL_FACTOR / ZOOM;
}

void SDLcam::update() {
    if (++counter * 2 * SCROLL_FACTOR >= FPS_CLIENT) {
        counter = 0;
        switch (this->direccion) {
            case CAM_UP:
                if (y > 0) this->y--;
                break;
            case CAM_RIGHT:
                if ((ceil(static_cast<float>(maxX + getX()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->x++;
                break;
            case CAM_DOWN:
                if ((ceil(static_cast<float>(maxY + getY()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->y++;
                break;
            case CAM_LEFT:
                if (x > 0) this->x--;
                break;

            case CAM_UL:
                if (y > 0) this->y--;
                if (x > 0) this->x--;
                break;

            case CAM_UR:
                if (y > 0) this->y--;
                if ((ceil(static_cast<float>(maxX + getX()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->x++;
                break;

            case CAM_DL:
                if ((ceil(static_cast<float>(maxY + getY()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->y++;
                if (x > 0) this->x--;
                break;

            case CAM_DR:
                if ((ceil(static_cast<float>(maxY + getY()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->y++;
                if ((ceil(static_cast<float>(maxX + getX()) / (CELL_SIZE * ZOOM))) < CELL_SIZE * ZOOM)
                    this->x++;
                break;

            default:
                break;
        }
    }
}
