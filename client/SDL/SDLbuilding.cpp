#include "SDLbuilding.h"

using namespace SDL2pp;

SDLbuilding::SDLbuilding(StBuilding &building, int house, YAML::Node data) : id(building.id),
                                                                             position(std::pair<int, int>(building.position.first * ZOOM,
                                                                                                          building.position.second * ZOOM)),
                                                                             health(building.hp),
                                                                             house(house),
                                                                             playerID(building.playerID),
                                                                             type(building.type),
                                                                             node(data),
                                                                             isSelected(false) {}

std::pair<int, int> SDLbuilding::getPosition() {
    return position;
}

int SDLbuilding::getId() {
    return id;
}

int SDLbuilding::getHealthImageID() {
    YAMLbuilding Ybuilding(node, type);

    if (Ybuilding.getHp() / 2 > health) {
        return 1;
    }
    return 0;
}

void SDLbuilding::isClicked(int x, int y) {
    if (isInside(x, y)) {
        isSelected = true;
    }
}

bool SDLbuilding::isInside(int x, int y) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    int adentroX = (x >= this->position.first && x < (this->position.first + tamanio.first * CELL_SIZE * ZOOM));
    int adentroY = (y >= this->position.second && y < (this->position.second + tamanio.second * CELL_SIZE * ZOOM));

    return (adentroX && adentroY);
}

int SDLbuilding::isClicked(int fromx, int fromy, int tox, int toy) {
    int adentroSO = (position.first >= fromx && position.first <= tox) && (position.second >= fromy && position.second <= toy);
    int adentroNE = (position.first <= fromx && position.first >= tox) && (position.second <= fromy && position.second >= toy);
    int adentroSE = (position.first <= fromx && position.first >= tox) && (position.second >= fromy && position.second <= toy);
    int adentroNO = (position.first >= fromx && position.first <= tox) && (position.second <= fromy && position.second >= toy);

    return (adentroSO || adentroNE || adentroSE || adentroNO);
}

void SDLbuilding::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
}

void SDLbuilding::renderSelected(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    if (isSelected) {
        renderer.Copy(
            *textures["selector"],
            Rect(0, 0, 32, 32),
            Rect(
                position.first - cam.getX(),
                position.second - cam.getY(),
                cam.turnToViewSize(tamanio.first),
                cam.turnToViewSize(tamanio.second)));
    }
}

void SDLbuilding::renderHealth(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    if (isSelected) {
        renderer.Copy(
            *textures["hp"],
            Rect(0, 0, 32, 16),
            Rect(
                position.first - cam.getX(),
                position.second - cam.turnToViewSize(tamanio.second) / 6 - cam.getY(),
                cam.turnToViewSize(tamanio.first),
                10));

        renderer.Copy(
            *textures["hpgreen"],
            Rect(0, 0, 32, 16),
            Rect(
                position.first - cam.getX(),
                position.second - cam.turnToViewSize(tamanio.second) / 6 - cam.getY(),
                cam.turnToViewSize(tamanio.first) * (static_cast<float>(health) / static_cast<float>(Ybuilding.getHp())),
                8));
    }

    renderDestroyed(renderer, cam, textures);
}

void SDLbuilding::renderBuild(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();
    if (buildingStage < 21) {
        renderer.Copy(
            *textures["create" + std::to_string(buildingStage / 3)],
            Rect(0, 0,
                 textures["create" + std::to_string(buildingStage / 3)]->GetWidth(),
                 textures["create" + std::to_string(buildingStage / 3)]->GetHeight()),
            Rect(
                position.first - cam.getX(),
                position.second - cam.getY(),
                cam.turnToViewSize(tamanio.first),
                cam.turnToViewSize(tamanio.second)));

        buildingStage++;
    }
}

void SDLbuilding::renderDestroyed(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();
    if (sDestruction && this->destroyedStage > 2) {
        renderer.Copy(
            *textures["destroyed" + std::to_string(this->destroyedStage / 3)],
            Rect(0, 0,
                 textures["destroyed" + std::to_string(this->destroyedStage / 3)]->GetWidth(),
                 textures["destroyed" + std::to_string(this->destroyedStage / 3)]->GetHeight()),
            Rect(
                position.first - cam.getX(),
                position.second - cam.getY(),
                cam.turnToViewSize(tamanio.first),
                cam.turnToViewSize(tamanio.second)));
        this->destroyedStage--;
    }
}

void SDLbuilding::removeSelected() {
    isSelected = false;
}

void SDLbuilding::update(StBuilding building, SDLsound &sounds) {
    health = building.hp;
    if (health > building.hp && !avisado && type == CONSTRUCTION_YARD && building.playerID == playerID) {
        sounds.playHouseSound("atackBase");
        avisado = true;
    }
}

int SDLbuilding::getPlayerID() {
    return playerID;
}

void SDLbuilding::startDestruction() {
    sDestruction = true;
}

bool SDLbuilding::getSDestruction() {
    return destroyedStage == 2;
}

SDLbuilding::~SDLbuilding() {
}
