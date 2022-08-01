#include "SDLunits.h"

using namespace SDL2pp;

SDLunits::SDLunits(Partida &partida, Renderer &renderer) : partida(std::move(partida)), renderer(renderer), yamlUnits(YAML::LoadFile("../assets.yaml")) {
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 32; j++) {
            std::string path = "../assets/units/" + std::to_string(i) + "/" + std::to_string(j) + ".png";
            std::string pathM = "../assets/units/" + std::to_string(i) + "/" + std::to_string(j) + "m.png";
            if (i == 6)
                sprites[{i, j}] = new Texture(renderer, Surface(path).SetColorKey(true, 0));
            else
                sprites[{i, j}] = new Texture(renderer, Surface(path).SetColorKey(true, 0xff00ff));
            Texture *textureM = new Texture(renderer, Surface(pathM).SetColorKey(true, 0));
            // sprites[{i, j}] = texture;
            mask[{i, j}] = textureM;
        }
    for (int i = 0; i < 30; i++) {
        std::string pathattack = "../assets/SDL/units/attack/" + std::to_string(i) + ".png";
        Texture *tex = new Texture(renderer, Surface(pathattack).SetColorKey(true, 0));
        textures["attack" + std::to_string(i)] = tex;
    }
}

void SDLunits::render(SDLgui &gui) {
    for (auto &unit : units) {
        bool inside = gui.getCamera().isInside(unit->getPosition());
        if (inside)
            unit->render(gui.getCamera(), textures, sprites, mask);
    }
}

void SDLunits::update(SDLsound &sounds) {
    for (auto &pUnit : partida.getUnits()) {
        int exists = this->exists(pUnit.id);
        if (exists != -1) {
            units[exists]->update(pUnit, sounds);
        } else {
            createUnit(pUnit, sounds);
        }
    }
    removeDead();
}

int SDLunits::exists(int id) {
    for (int i = 0; i < units.size(); i++) {
        if (id == units[i]->getId()) {
            return i;
        }
    }
    return -1;
}

void SDLunits::createUnit(StUnit &unit, SDLsound &sounds) {
    units.push_back(std::shared_ptr<SDLunit>(new SDLunit(unit, partida.getHouse(), yamlUnits, renderer, sounds)));
}

void SDLunits::removeSelected() {
    for (auto &unit : units) {
        unit->removeSelected();
    }
}

std::vector<std::shared_ptr<SDLunit>> SDLunits::getUnits() {
    return units;
}

void SDLunits::removeDead() {
    std::vector<int> dead;
    for (int i = 0; i < units.size(); i++) {
        bool exists = false;
        for (auto &bunit : partida.getUnits()) {
            if (units[i]->getId() == bunit.id) {
                exists = true;
            }
        }
        if (!exists) {
            dead.push_back(i);
        }
    }

    for (auto &dest : dead) {
        units.erase(units.begin() + dest);
    }
}

int SDLunits::getEnemyIdInPosition(std::pair<int, int> position) {
    auto units_it = std::find_if(units.begin(), units.end(), [&](std::shared_ptr<SDLunit> &unit) {
        return unit->isInside(position.first, position.second) && (unit->getPlayerID() != partida.getPlayerID());
    });
    if (units_it == units.end()) {
        return -1;
    }
    return (*units_it)->getId();
}

int SDLunits::getAllyIdInPosition(std::pair<int, int> position) {
    auto units_it = std::find_if(units.begin(), units.end(), [&](std::shared_ptr<SDLunit> &unit) {
        return unit->isInside(position.first, position.second) && (unit->getPlayerID() == partida.getPlayerID());
    });
    if (units_it == units.end()) {
        return -1;
    }
    return (*units_it)->getId();
}

std::vector<int> SDLunits::getSelectedUnits() {
    std::vector<int> selected;
    for (auto &unit : units) {
        if (unit->getSelected())
            selected.push_back(unit->getId());
    }
    return selected;
}

SDLunits::~SDLunits() {
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 32; j++) {
            delete sprites[{i, j}];
            delete mask[{i, j}];
        }
}
