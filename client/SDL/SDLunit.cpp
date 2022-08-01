#include "SDLunit.h"

using namespace SDL2pp;

SDLunit::SDLunit(StUnit &unit, int house, YAML::Node data, Renderer &renderer, SDLsound &sounds) : id(unit.id),
                                                                                                   position(std::pair<int, int>(unit.position.first * ZOOM,
                                                                                                                                unit.position.second * ZOOM)),
                                                                                                   heading(unit.heading),
                                                                                                   house(house),
                                                                                                   type(unit.type),
                                                                                                   health(unit.hp),
                                                                                                   playerID(unit.playerID),
                                                                                                   renderer(renderer),
                                                                                                   attacking(unit.attacking) {
    this->Yunits = data;
    this->isSelected = false;
    sounds.playHouseSound("unitReady");
    offset = {{{0, 0}, {5, 12}},
              {{0, 1}, {2, 12}},
              {{0, 2}, {2, 12}},
              {{0, 3}, {3, 12}},
              {{0, 4}, {5, 12}},
              {{0, 5}, {6, 12}},
              {{0, 6}, {5, 12}},
              {{0, 7}, {7, 12}},
              {{0, 8}, {5, 12}},
              {{0, 9}, {-1, 13}},
              {{0, 10}, {3, 12}},
              {{0, 11}, {3, 10}},
              {{0, 12}, {5, 12}},
              {{0, 13}, {5, 12}},
              {{0, 14}, {6, 12}},
              {{0, 15}, {6, 12}},
              {{0, 16}, {5, 12}},
              {{0, 17}, {0, 13}},
              {{0, 18}, {0, 12}},
              {{0, 19}, {1, 10}},
              {{0, 20}, {5, 11}},
              {{0, 21}, {5, 12}},
              {{0, 22}, {6, 12}},
              {{0, 23}, {7, 12}},
              {{0, 24}, {5, 12}},
              {{0, 25}, {-1, 13}},
              {{0, 26}, {0, 12}},
              {{0, 27}, {1, 10}},
              {{0, 28}, {5, 12}},
              {{0, 29}, {5, 12}},
              {{0, 30}, {4, 12}},
              {{0, 31}, {6, 12}},
              {{0, 32}, {5, 12}},
              {{0, 33}, {-1, 13}},
              {{0, 34}, {2, 12}},
              {{0, 35}, {1, 10}},
              {{0, 36}, {4, 12}},
              {{0, 37}, {5, 12}},
              {{0, 38}, {3, 12}},
              {{0, 39}, {7, 12}},
              {{0, 40}, {6, 12}},
              {{0, 41}, {-1, 13}},
              {{0, 42}, {2, 12}},
              {{0, 43}, {0, 10}},
              {{0, 44}, {2, 12}},
              {{0, 45}, {5, 12}},
              {{0, 46}, {4, 12}},
              {{0, 47}, {7, 12}},
              {{0, 48}, {6, 12}},
              {{0, 49}, {-1, 13}},
              {{0, 50}, {0, 12}},
              {{0, 51}, {0, 10}},
              {{0, 52}, {3, 12}},
              {{0, 53}, {5, 12}},
              {{0, 54}, {5, 12}},
              {{0, 55}, {7, 12}}};
}

std::pair<int, int> SDLunit::getPosition() {
    return std::pair<int, int>(position.first, position.second);
}

int SDLunit::getId() {
    return id;
}

void SDLunit::isClicked(int x, int y, SDLsound &sounds) {
    if (isInside(x, y)) {
        isSelected = true;
        sounds.playUnitSelect(type);
    }
}

bool SDLunit::isInside(int x, int y) {
    int adentroX = (x >= this->position.first - xoff && x <= this->position.first + spriteW);
    int adentroY = (y >= this->position.second - yoff && y <= this->position.second + spriteH);

    return (adentroX && adentroY);
}

bool SDLunit::isInsideTile(int x, int y) {
    int adentroX = (x <= this->position.first && (x + CELL_SIZE * ZOOM) >= this->position.first);
    int adentroY = (y <= this->position.second && (y + CELL_SIZE * ZOOM) >= this->position.second);

    int adentroXX = (x <= this->position.first + spriteW && (x + CELL_SIZE * ZOOM) >= this->position.first + spriteW);
    int adentroYY = (y <= this->position.second + spriteH && (y + CELL_SIZE * ZOOM) >= this->position.second + spriteH);

    return ((adentroX && adentroY) || (adentroXX && adentroYY));
}

void SDLunit::isClicked(std::pair<int, int> from, std::pair<int, int> to) {
    int fromx = from.first;
    int fromy = from.second;
    int tox = to.first;
    int toy = to.second;

    int adentroSO = (position.first >= fromx && position.first <= tox) &&
                    (position.second >= fromy && position.second <= toy);
    int adentroNE = (position.first <= fromx && position.first >= tox) &&
                    (position.second <= fromy && position.second >= toy);
    int adentroSE = (position.first <= fromx && position.first >= tox) &&
                    (position.second >= fromy && position.second <= toy);
    int adentroNO = (position.first >= fromx && position.first <= tox) &&
                    (position.second <= fromy && position.second >= toy);

    if (adentroSO || adentroNE || adentroSE || adentroNO) {
        isSelected = true;
    }
}

void SDLunit::setColorMod(Texture &mask) {
    int r = (playerID * 250) % 255;
    int g = (playerID * 80 + 70) % 255;
    int b = (playerID * 20 + 180) % 255;
    mask.SetColorMod(r, g, b);
}

void SDLunit::render(SDLcam &cam,
                     std::map<std::string, Texture *> &textures,
                     std::map<std::pair<int, int>, Texture *> &sprites,
                     std::map<std::pair<int, int>, Texture *> &mask) {
    std::pair<int, int> p;
    if (type < 4) {
        p = {type, frame + heading / 4};
    } else {
        p = {type, heading};
    }

    sprites[p]->SetBlendMode(SDL_BLENDMODE_BLEND);
    setColorMod(*mask[p]);

    if (type == 0) {
        xoff = offset[{type, frame + heading / 4}].first * ZOOM;
        yoff = offset[{type, frame + heading / 4}].second * ZOOM;
    }
    spriteW = sprites[p]->GetWidth() * ZOOM;
    spriteH = sprites[p]->GetHeight() * ZOOM;

    renderer.Copy(
        *sprites[p],
        Rect(
            0,
            0,
            sprites[p]->GetWidth(),
            sprites[p]->GetHeight()),
        Rect(
            position.first - xoff - cam.getX(),
            position.second - yoff - cam.getY(),
            spriteW,
            spriteH));

    renderer.Copy(
        *mask[p],
        Rect(
            0,
            0,
            mask[p]->GetWidth(),
            mask[p]->GetHeight()),
        Rect(
            position.first - xoff - cam.getX(),
            position.second - yoff - cam.getY(),
            spriteW,
            spriteH));
    if (isSelected) {
        Texture selector(
            renderer,
            Surface("../assets/sel.png").SetColorKey(true, 0));

        renderer.Copy(
            selector,
            Rect(0, 0, CELL_SIZE, CELL_SIZE),
            Rect(
                position.first - xoff - cam.getX() - (-spriteW / 2 + CELL_SIZE),
                position.second - yoff - cam.getY() - (-spriteH / 2 + CELL_SIZE),
                CELL_SIZE * ZOOM,
                CELL_SIZE * ZOOM));
    }

    interleave++;
    interleave %= 16;
    if (interleave == 0) {
        frame += 8;
        if (frame == 32) frame = 8;
    }

    renderHealth(cam);
    renderAttack(cam, textures);
}

bool SDLunit::getSelected() {
    return isSelected;
}

void SDLunit::renderAttack(SDLcam &cam, std::map<std::string, Texture *> &textures) {
    if (attacking) {
        attackVal++;
        if ((attackVal % 3) == 0) {
            getHeadingAttack();
            YAMLunit Yunit(Yunits, type);

            float first = position.first - xoff - cam.getX() + attackX;
            float second = position.second - yoff - cam.getY() + attackY;

            if (heading < 30) {
                renderer.Copy(
                    *textures["attack" + std::to_string(heading)],
                    Rect(0, 0, 32, 32),
                    Rect(
                        first,
                        second,
                        16,
                        16));
            }
        }
    }
}

void SDLunit::getHeadingAttack() {
    if (heading == 0) {
        attackX = (+spriteW / 2);
        attackY = (+spriteH / 4);
    } else if (heading == 8) {
        attackX = (+spriteW / 2);
        attackY = 0;
    } else if (heading == 16) {
        attackX = (+spriteW / 2);
        attackY = (+spriteH / 2);
    } else if (heading == 24) {
        attackX = 0;
        attackY = (-spriteH / 4);
    } else if (heading == 4) {
        attackX = (+spriteW / 2);
        attackY = (-spriteH / 2);
    } else if (heading == 12) {
        attackX = (+spriteW / 2);
        attackY = (+spriteH / 2);
    } else if (heading == 20) {
        attackX = (-spriteW / 2);
        attackY = (+spriteH / 2);
    } else if (heading == 28) {
        attackX = (-spriteW / 2);
        attackY = (-spriteH / 2);
    }
}

void SDLunit::renderHealth(SDLcam &cam) {
    if (isSelected) {
        YAMLunit Yunit(Yunits, type);

        float first = position.first - xoff - cam.getX() - (-spriteW / 2 + CELL_SIZE);
        float second = position.second - yoff - cam.getY() - (-spriteH / 2 + 10 + CELL_SIZE);

        Texture hpp(
            renderer,
            Surface("../assets/hp.png"));

        renderer.Copy(
            hpp,
            Rect(0, 0, 32, 32),
            Rect(
                first,
                second,
                CELL_SIZE * ZOOM,
                8));

        Texture hp(
            renderer,
            Surface("../assets/hpgreen.png").SetColorMod(0, 255, 0));

        renderer.Copy(
            hp,
            Rect(0, 0, 32, 32),
            Rect(
                first,
                second,
                (CELL_SIZE * ZOOM) * float(health) / float(Yunit.getHp()),
                6));
    }
}

void SDLunit::removeSelected() {
    isSelected = false;
}

void SDLunit::update(StUnit unit, SDLsound &sounds) {
    position = std::pair<int, int>(unit.position.first * ZOOM,
                                   unit.position.second * ZOOM);
    heading = unit.heading;
    if (health > unit.hp && !avisado && unit.playerID == playerID) {
        sounds.playHouseSound("atackBase");
        avisado = true;
    }
    health = unit.hp;
    attacking = unit.attacking;
}

int SDLunit::getPlayerID() {
    return playerID;
}

SDLunit::~SDLunit() {
}
