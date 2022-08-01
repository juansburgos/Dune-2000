#include "SDLmap.h"

using namespace SDL2pp;

SDLmap::SDLmap(Partida &partida,
               Renderer &renderer,
               Texture &texture) : partida(std::move(partida)),
                                   renderer(renderer),
                                   texture(texture) {
}

void SDLmap::setTiles(const std::vector<std::vector<int>> tiles) {
    this->tiles = tiles;
}

void SDLmap::setSpices(const std::vector<std::vector<int>> spices) {
    this->spices = spices;
}

int SDLmap::getTileType(std::pair<int, int> position) {
    return tiles[position.second][position.first];
}

int SDLmap::getSpiceType(std::pair<int, int> position) {
    switch (spices[position.second][position.first]) {
        case 1:
            return 748;
        case 2:
            return 301;
        default:
            return 0;
    }
}

void SDLmap::renderTiles(SDLgui &gui) {
    setTiles(this->partida.getTiles());

    std::pair<int, int> position;
    for (position.second = 0; position.second < tiles.size(); position.second++) {
        for (position.first = 0; position.first < tiles[0].size(); position.first++) {
            if (gui.getCamera().tileIsInside(position)) {
                this->renderer.Copy(
                    this->texture,
                    Rect(
                        (getTileType(position) % 20) * CELL_SIZE,
                        (getTileType(position) / 20) * CELL_SIZE,
                        CELL_SIZE,
                        CELL_SIZE),
                    Rect(
                        (position.first * CELL_SIZE * ZOOM - gui.getCamera().getX()),
                        (position.second * CELL_SIZE * ZOOM - gui.getCamera().getY()),
                        CELL_SIZE * ZOOM,
                        CELL_SIZE * ZOOM));
            }
        }
    }
}

void SDLmap::renderSpices(SDLgui &gui) {
    setSpices(this->partida.getSpecia());

    std::pair<int, int> position;
    for (position.second = 0; position.second < tiles.size(); position.second++) {
        for (position.first = 0; position.first < tiles[0].size(); position.first++) {
            if (gui.getCamera().tileIsInside(position)) {
                if (getSpiceType(position) != 0) {
                    this->renderer.Copy(
                        this->texture,
                        Rect(
                            (getSpiceType(position) % 20) * CELL_SIZE,
                            (getSpiceType(position) / 20) * CELL_SIZE,
                            CELL_SIZE,
                            CELL_SIZE),
                        Rect(
                            (position.first * CELL_SIZE * ZOOM - gui.getCamera().getX()),
                            (position.second * CELL_SIZE * ZOOM - gui.getCamera().getY()),
                            CELL_SIZE * ZOOM,
                            CELL_SIZE * ZOOM));
                }
            }
        }
    }
}

void SDLmap::render(SDLgui &gui) {
    renderTiles(gui);
    renderSpices(gui);
}

std::string SDLmap::getColorCanBuild(int x, int y) {
    std::pair<int, int> pos(x, y);
    int type = tileType[getTileType(pos)];
    if (type == 4) return "green";
    return "red";
}