#include "SDLbuildings.h"

using namespace SDL2pp;

SDLbuildings::SDLbuildings(Partida &partida, Renderer &renderer) : partida(std::move(partida)), renderer(renderer), yamlBuildings(YAML::LoadFile("../assets.yaml")) {
    textures["selector"] = new Texture(renderer, Surface("../assets/sel.png").SetColorKey(true, 0));
    textures["hp"] = new Texture(renderer, Surface("../assets/hp.png"));
    textures["hpgreen"] = new Texture(renderer, Surface("../assets/hpgreen.png").SetColorMod(0, 255, 0));

    for (int i = 0; i <= 7; i++) {
        textures["create" + std::to_string(i)] = new Texture(renderer, Surface("../assets/SDL/buildings/create/" + std::to_string(i) + ".png").SetColorKey(true, 0xff00ff));
    }

    for (int i = 1; i <= 14; i++) {
        textures["destroyed" + std::to_string(i)] = new Texture(renderer, Surface("../assets/SDL/buildings/explode/" + std::to_string(i) + ".png").SetColorKey(true, 0xff00ff));
    }

    textures["AirTrap"] = new Texture(renderer, Surface("../assets/buildings/2.png"));
    textures["CYard"] = new Texture(renderer, Surface("../assets/buildings/0.png"));
    textures["LFactory"] = new Texture(renderer, Surface("../assets/buildings/1.png"));
    textures["palace"] = new Texture(renderer, Surface("../assets/buildings/7.png"));
    textures["silo"] = new Texture(renderer, Surface("../assets/buildings/5.png"));

    for (int i = 0; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            textures[std::to_string(6) + std::to_string(i) + std::to_string(j)] = new Texture(renderer, Surface("../assets/buildings/" + std::to_string(6) + std::to_string(i) + std::to_string(j) + ".png"));
            textures[std::to_string(3) + std::to_string(i) + std::to_string(j)] = new Texture(renderer, Surface("../assets/buildings/" + std::to_string(3) + std::to_string(i) + std::to_string(j) + ".png"));
        }
        for (int k = 0; k <= 2; k++) {
            textures[std::to_string(4) + std::to_string(i) + std::to_string(k)] = new Texture(renderer, Surface("../assets/buildings/" + std::to_string(4) + "/" + std::to_string(i) + std::to_string(k) + ".png"));
        }
    }
}

void SDLbuildings::render(SDLgui &gui) {
    for (auto &building : buildings) {
        bool inside = gui.getCamera().isInside(building->getPosition());
        if (inside)
            building->render(renderer, gui.getCamera(), textures);
    }
}

void SDLbuildings::update(SDLsound &sounds) {
    for (auto &pBuilding : partida.getBuildings()) {
        int exists = this->exists(pBuilding.id);
        if (exists != -1) {
            buildings[exists]->update(pBuilding, sounds);
        } else {
            createBuilding(pBuilding);
        }
    }
    removeDestroyed();
}

int SDLbuildings::exists(int id) {
    for (int i = 0; i < buildings.size(); i++) {
        if (id == buildings[i]->getId()) {
            return i;
        }
    }
    return -1;
}

void SDLbuildings::createBuilding(StBuilding &building) {
    switch (building.type) {
        case CONSTRUCTION_YARD:
            buildings.push_back(std::shared_ptr<SDLConstructionYard>(new SDLConstructionYard(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case LIGHT_FACTORY:
            buildings.push_back(std::shared_ptr<SDLLightFactory>(new SDLLightFactory(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case AIR_TRAP:
            buildings.push_back(std::shared_ptr<SDLAirTrap>(new SDLAirTrap(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case REFINERY:
            buildings.push_back(std::shared_ptr<SDLRefinery>(new SDLRefinery(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case HEAVY_FACTORY:
            buildings.push_back(std::shared_ptr<SDLHeavyFactory>(new SDLHeavyFactory(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case SPICE_SILO:
            buildings.push_back(std::shared_ptr<SDLSpiceSilo>(new SDLSpiceSilo(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case BARRACKS:
            buildings.push_back(std::shared_ptr<SDLBarracks>(new SDLBarracks(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        case PALACE:
            buildings.push_back(std::shared_ptr<SDLPalace>(new SDLPalace(building, partida.getPlayerHouse(building.playerID), yamlBuildings)));
            break;
        default:
            break;
    }
}

void SDLbuildings::removeDestroyed() {
    for (auto &build : buildings) {
        auto building_it = std::find_if(partida.getBuildings().begin(), partida.getBuildings().end(), [&build](const StBuilding &building) {
            return build->getId() == building.id;
        });
        if (building_it == partida.getBuildings().end()) {
            build->startDestruction();
        }
    }

    buildings.erase(
        std::remove_if(
            buildings.begin(),
            buildings.end(),
            [](std::shared_ptr<SDLbuilding> &b) { return b->getSDestruction(); }),
        buildings.end());
}

void SDLbuildings::removeSelected() {
    for (auto &building : buildings) {
        building->removeSelected();
    }
}

int SDLbuildings::getEnemyIdInPosition(std::pair<int, int> position) {
    auto building_it = std::find_if(buildings.begin(), buildings.end(), [&](std::shared_ptr<SDLbuilding> &building) {
        return building->isInside(position.first, position.second) && (building->getPlayerID() != partida.getPlayerID());
    });
    if (building_it == buildings.end()) {
        return -1;
    }
    return (*building_it)->getId();
}

int SDLbuildings::getAllyIdInPosition(std::pair<int, int> position) {
    auto building_it = std::find_if(buildings.begin(), buildings.end(), [&](std::shared_ptr<SDLbuilding> &building) {
        return building->isInside(position.first, position.second) && (building->getPlayerID() == partida.getPlayerID());
    });
    if (building_it == buildings.end()) {
        return -1;
    }
    return (*building_it)->getId();
}

std::vector<std::shared_ptr<SDLbuilding>> SDLbuildings::getBuildings() {
    return buildings;
}

std::pair<int, int> SDLbuildings::getBuildingDimension(int type) {
    YAMLbuilding Ybuilding(yamlBuildings, type);
    return Ybuilding.getDimensions();
}

SDLbuildings::~SDLbuildings() {
    for (const auto &text : textures) {
        delete text.second;
    }
}