#include "SDLmenu.h"

SDLmenu::SDLmenu(int windowWidth, int windowHeight, int house, Renderer &renderer, Partida &partida) : minW(windowWidth * GUI_MAP_WIDTH),
                                                                                                       maxW(windowWidth),
                                                                                                       minH(0),
                                                                                                       maxH(windowHeight),
                                                                                                       renderer(renderer),
                                                                                                       house(house),
                                                                                                       yamlAssets(YAML::LoadFile("../assets.yaml")) {
    for (int i = 0; i < 8; i++) {
        // bool has = std::find(partida.getBuildingsToCreate().begin(), partida.getBuildingsToCreate().end(), i) != partida.getBuildingsToCreate().end();
        buildings.push_back(SDLmenuicon(windowWidth, windowHeight, house, 0, i, partida, yamlAssets));
    }
    for (int i = 0; i < 11; i++) {
        // bool has = std::find(partida.getUnitsToCreate().begin(), partida.getUnitsToCreate().end(), i) != partida.getUnitsToCreate().end();
        units.push_back(SDLmenuicon(windowWidth, windowHeight, house, 1, i, partida, yamlAssets));
    }

    int r = (partida.getPlayerID() * 250) % 255;
    int g = (partida.getPlayerID() * 80 + 70) % 255;
    int b = (partida.getPlayerID() * 20 + 180) % 255;

    textures["menu-skeleton"] = new Texture(renderer, Surface("../assets/SDL/menu/menu2.png"));
    textures["white"] = new Texture(renderer, Surface("../assets/SDL/menu/white.png").SetColorMod(r, g, b));

    textures["house"] = new Texture(renderer, Surface("../assets/SDL/menu/house/" + std::to_string(house) + ".png"));

    for (int i = 0; i < 11; i++) {
        textures["1" + std::to_string(i)] = new Texture(renderer, Surface("../assets/SDL/menu/icons/1/" + std::to_string(i) + ".bmp").SetColorKey(true, 0));
    }

    for (int i = 0; i < 8; i++) {
        textures["0" + std::to_string(i) + std::to_string(house)] = new Texture(renderer, Surface("../assets/SDL/menu/icons/0/" + std::to_string(i) + "/" + std::to_string(house) + ".bmp").SetColorKey(true, 0));
    }

    textures["black"] = new Texture(renderer, Surface("../assets/SDL/menu/icons/black.png").SetAlphaMod(150));
    textures["green"] = new Texture(renderer, Surface("../assets/SDL/menu/icons/green.png").SetAlphaMod(150));
    textures["grey"] = new Texture(renderer, Surface("../assets/SDL/menu/icons/grey.png").SetAlphaMod(150));
}

void SDLmenu::render() {
    renderer.Copy(
        *textures["black"],
        Rect(0, 0, 290, 720),
        Rect(
            minW, minH,
            maxW * 0.2,
            maxH));

    renderer.Copy(
        *textures["white"],
        Rect(0, 0, 290, 720),
        Rect(
            minW, minH,
            maxW * 0.2,
            maxH * 0.35));

    renderer.Copy(
        *textures["menu-skeleton"],
        Rect(0, 0, 290, 720),
        Rect(
            minW, minH,
            maxW * GUI_MENU_WIDTH,
            maxH));
}

void SDLmenu::renderHouseIcon() {
    renderer.Copy(
        *textures["house"],
        Rect(0, 0, 128, 128),
        Rect(
            minW + (maxW * 0.005),
            0,
            maxW * (GUI_MENU_WIDTH - 0.01),
            maxH * 0.35));
}

void SDLmenu::renderBuildings() {
    int pos = 0;
    for (int i = initBuildings; i < (initBuildings + 6); i++) {
        if (i < 8) {
            buildings[i].render(renderer, textures, pos);
            pos++;
        }
    }
}

void SDLmenu::renderUnits() {
    int pos = 0;
    for (int i = initUnits; i < (initUnits + 6); i++) {
        if (i < 11) {
            units[i].render(renderer, textures, pos);
            pos++;
        }
    }
}

void SDLmenu::update(int windowWidth, int windowHeight, Partida &partida) {
    minW = windowWidth * GUI_MAP_WIDTH;
    maxW = windowWidth;
    minH = 0;
    maxH = windowHeight;

    for (auto &b : buildings) {
        // bool has = std::find(partida.getBuildingsToCreate().begin(), partida.getBuildingsToCreate().end(), b.getType()) != partida.getBuildingsToCreate().end();
        b.updateWindow(windowWidth, windowHeight, partida);
    }

    for (auto &u : units) {
        // bool has = std::find(partida.getUnitsToCreate().begin(), partida.getUnitsToCreate().end(), u.getType()) != partida.getUnitsToCreate().end();
        u.updateWindow(windowWidth, windowHeight, partida);
    }
}

void SDLmenu::handleClick(int x, int y, int &createBuilding, int &createUnit, bool &destroyBuilding) {
    destroyBuilding = false;

    if (x > (minW + maxW * GUI_MENU_WIDTH * 0.1) && x < (minW + maxW * GUI_MENU_WIDTH * 0.5 / 1.8) && y > maxH * 0.93 && y < maxH) {
        if (initBuildings > 0) initBuildings--;
    } else if (x > (minW + maxW * GUI_MENU_WIDTH * 0.25) && x < (minW + maxW * GUI_MENU_WIDTH * 0.45) && y > maxH * 0.93 && y < maxH) {
        if (initBuildings < 2) initBuildings++;
    } else if (x > (minW + maxW * GUI_MENU_WIDTH * 0.5) && x < (minW + maxW * GUI_MENU_WIDTH * 0.7) && y > maxH * 0.93 && y < maxH) {
        if (initUnits > 0) initUnits--;
    } else if (x > (minW + maxW * GUI_MENU_WIDTH * 0.71) && x < (minW + maxW * GUI_MENU_WIDTH * 0.88) && y > maxH * 0.93 && y < maxH) {
        if (initUnits < 5) initUnits++;
    } else if (x > (minW + maxW * GUI_MENU_WIDTH * 0.4) && x < (minW + maxW * GUI_MENU_WIDTH * 0.6) && y > maxH * 0.35 && y < maxH * 0.45) {
        destroyBuilding = true;
    } else {
        for (auto &building : buildings) {
            building.handleClick(x, y, createBuilding, createUnit);
        }

        for (auto &unit : units) {
            unit.handleClick(x, y, createBuilding, createUnit);
        }
    }
}

SDLmenu::~SDLmenu() {
    for (const auto &text : textures) {
        delete text.second;
    }
}
