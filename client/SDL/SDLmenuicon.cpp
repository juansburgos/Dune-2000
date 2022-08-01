#include "SDLmenuicon.h"

SDLmenuicon::SDLmenuicon(int windowWidth, int windowHeight, int house, int self, int type, Partida &partida, YAML::Node data) : minW(windowWidth * GUI_MAP_WIDTH),
                                                                                                                                maxW(windowWidth),
                                                                                                                                minH(0),
                                                                                                                                maxH(windowHeight),
                                                                                                                                xi(maxW * (self == 1 ? (GUI_MAP_WIDTH + GUI_MENU_WIDTH / 2 + 0.002) : GUI_MAP_WIDTH + 0.025)),
                                                                                                                                yi(maxH * 0.46 + ((maxH * 0.0784) * 1)),
                                                                                                                                xf(maxW * (GUI_MENU_WIDTH - 0.05) / 2),
                                                                                                                                yf(maxH * 0.0784),
                                                                                                                                house(house),
                                                                                                                                self(self),
                                                                                                                                type(type),
                                                                                                                                partida(std::move(partida)) {
    if (self != 1) {
        YAMLbuilding Ybuilding(data, type);
        costo = Ybuilding.getCost();
        energy = Ybuilding.getEnergy();

        if (partida.getMoney() >= costo) {
            available = true;
        } else {
            available = false;
        }
    } else {
        YAMLunit Yunit(data, type);
        costo = Yunit.getCost();
        required = Yunit.getRequired();
        if (partida.getMoney() >= costo) {
            bool exists = true;
            for (auto &building : required) {
                auto found = std::find_if(
                    partida.getBuildings().begin(), partida.getBuildings().end(),
                    [building, &partida, Yunit](const StBuilding &ptr) {
                        return building == ptr.type && ptr.playerID == partida.getPlayerID();
                    });

                if (found == std::end(partida.getBuildings())) {
                    exists = false;
                }

                // auto found = std::find_if(
                //     partida.getBuildings().begin(), partida.getBuildings().end(),
                //     [building, &partida, Yunit](const StBuilding &ptr) {
                //         return building == ptr.type && ptr.playerID == partida.getPlayerID();
                //     });

                // if (found == std::end(partida.getBuildings())) {
                //     exists = false;
                // }
            }

            if (exists)
                available = true;
            else
                available = false;
        } else {
            available = false;
        }
    }
}

void SDLmenuicon::render(Renderer &renderer, std::map<std::string, Texture *> &textures, int position) {
    pos = position;

    std::string path = "";

    if (self == 1) {
        path += std::to_string(self) + std::to_string(type);
    } else {
        path += std::to_string(self) + std::to_string(type) + std::to_string(house);
    }

    renderer.Copy(
        *textures[path],
        Rect(0, 0, 60, 47),
        Rect(xi, yi, xf, yf));

    if (available) {
        if (enPreparacion && time < 100) {
            textures["black"]->SetBlendMode(SDL_BLENDMODE_BLEND);

            renderer.Copy(
                *textures["black"],
                Rect(0, 0, 60, 47),
                Rect(xi, yi, xf, yf * 0.01 * time));

            if (self != 1)
                time++;
        } else {
            enPreparacion = false;
        }

        if (time == 100) {
            preparado = true;
            textures["green"]->SetBlendMode(SDL_BLENDMODE_BLEND);
            renderer.Copy(
                *textures["green"],
                Rect(0, 0, 60, 47),
                Rect(xi, yi, xf, yf));
        }
    } else {
        textures["grey"]->SetBlendMode(SDL_BLENDMODE_BLEND);

        renderer.Copy(
            *textures["grey"],
            Rect(0, 0, 60, 47),
            Rect(xi, yi, xf, yf));
    }
}

void SDLmenuicon::updateWindow(int windowWidth, int windowHeight, Partida &partida) {
    minW = windowWidth * GUI_MAP_WIDTH;
    maxW = windowWidth;
    minH = 0;
    maxH = windowHeight;
    xi = maxW * (self ? (GUI_MAP_WIDTH + GUI_MENU_WIDTH / 2 + 0.002) : GUI_MAP_WIDTH + 0.025);
    yi = maxH * 0.46 + ((maxH * 0.0784) * pos);
    xf = maxW * (GUI_MENU_WIDTH - 0.05) / 2;
    yf = maxH * 0.0784;

    if (partida.getMoney() >= costo || time > 0) {
        if (self != 1) {
            available = true;
        } else {
            bool exists = true;
            for (auto &building : required) {
                auto found = std::find_if(
                    partida.getBuildings().begin(), partida.getBuildings().end(),
                    [building, &partida](const StBuilding &ptr) {
                        return building == ptr.type && ptr.playerID == partida.getPlayerID();
                    });

                if (found == std::end(partida.getBuildings())) {
                    exists = false;
                }
            }

            if (exists) {
                available = true;
                time = partida.getPercentOnHold(type);
            } else {
                available = false;
            }
        }
    } else {
        available = false;
    }
}

void SDLmenuicon::handleClick(int x, int y, int &createBuilding, int &createUnit) {
    if (isInside(x, y) && !enPreparacion && !preparado && time < 100 && available) {
        enPreparacion = true;
        if (self) {
            createUnit = type;
        } else {
            createBuilding = -1;
        }
    } else if (isInside(x, y) && !enPreparacion && preparado && available) {
        time = 0;
        preparado = false;
        if (self) {
            createUnit = type;
        } else {
            createBuilding = type;
        }
    }
}

int SDLmenuicon::getType() {
    return type;
}

bool SDLmenuicon::isInside(int x, int y) {
    return (xi < x && x < xi + xf && yi < y && y < yi + yf);
}
