#include "SDLgame.h"

using namespace SDL2pp;

SDLgame::SDLgame(Partida &partida,
                 Window &window,
                 Renderer &renderer,
                 Texture &texture,
                 ClientQueue &queue) : window(window),
                                       renderer(renderer),
                                       mapTexture(texture),
                                       gui(window, renderer, partida),
                                       map(partida, renderer, mapTexture),
                                       units(partida, renderer),
                                       buildings(partida, renderer),
                                       queue(queue),
                                       partida(partida),
                                       is_running(true),
                                       font(Font("../assets/SDL/ttf/Vera.ttf", 30)),
                                       sounds(partida.getHouse()),
                                       wormPosition(std::pair<int, int>(0, 0)) {
    textures["cursor"] = new Texture(renderer, Surface("../assets/SDL/cursor/cursors.png"));
    textures["green"] = new Texture(renderer, Surface("../assets/SDL/menu/icons/green.png").SetAlphaMod(150));
    textures["red"] = new Texture(renderer, Surface("../assets/SDL/menu/icons/red.png").SetAlphaMod(150));
    textures["green"]->SetBlendMode(SDL_BLENDMODE_BLEND);
    textures["red"]->SetBlendMode(SDL_BLENDMODE_BLEND);
    for (int i = 0; i <= 15; i++) {
        textures["worm" + std::to_string(i)] = new Texture(renderer, Surface("../assets/SDL/worm/" + std::to_string(i) + ".png").SetColorKey(true, 0));
    }
}

bool SDLgame::isRunning() {
    return this->is_running;
}

void SDLgame::handleEvents() {
    SDL_Event env;

    while (SDL_PollEvent(&env) != 0) {
        switch (env.type) {
            case SDL_QUIT:
                this->is_running = false;
                break;

            case SDL_KEYDOWN:
                switch (env.key.keysym.sym) {
                    case SDLK_q:
                        this->is_running = false;
                        break;
                    case SDLK_RIGHT:
                        gui.getCamera().setDireccion(CAM_RIGHT);
                        break;
                    case SDLK_LEFT:
                        gui.getCamera().setDireccion(CAM_LEFT);
                        break;
                    case SDLK_UP:
                        gui.getCamera().setDireccion(CAM_UP);
                        break;
                    case SDLK_DOWN:
                        gui.getCamera().setDireccion(CAM_DOWN);
                        break;
                }
                break;

            case SDL_KEYUP:
                gui.getCamera().setDireccion(CAM_CENTER);
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (env.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&selectFromX, &selectFromY);

                    if (createBuilding != -1 && createBuildingOK) {
                        std::pair<int, int> position(env.button.x, env.button.y);
                        gui.getCamera().setToViewSize(position);
                        auto cMsgConstrir = std::make_shared<CMsgConstruir>(createBuilding, partida.getPlayerID(), position);
                        queue.push(cMsgConstrir);
                        createBuilding = -1;
                    }

                    if (destroyBuilding) {
                        std::pair<int, int> cursor = gui.getCamera().turnToViewSize(std::pair<int, int>(selectFromX, selectFromY));
                        int buildingID = buildings.getAllyIdInPosition(cursor);
                        if (buildingID != -1){
                          auto cMsgDestruir = std::make_shared<CMsgDestruir>(partida.getPlayerID(), buildingID);
                          queue.push(cMsgDestruir);
                          destroyBuilding = false;
                        }
                    }

                    gui.getMenu().handleClick(selectFromX, selectFromY, createBuilding, createUnit, destroyBuilding);

                    if (createUnit != -1) {
                        std::pair<int, int> position = {0, 0};
                        auto cMsgCrearUnidad = std::make_shared<CMsgCrearUnidad>(createUnit, partida.getPlayerID(), position);
                        queue.push(cMsgCrearUnidad);
                        createUnit = -1;
                    }
                }

                if (env.button.button == SDL_BUTTON_RIGHT) {
                    createBuilding = -1;
                    destroyBuilding = false;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (env.button.button == SDL_BUTTON_LEFT && createBuilding == -1 && createUnit == -1) {
                    if (selectFromX == env.button.x && selectFromY == env.button.y) {
                        select();
                    } else {
                        checkMultpleSelection(env.button.x, env.button.y);
                    }
                }

                if (env.button.button == SDL_BUTTON_RIGHT && createBuilding == -1 && createUnit == -1) {
                    std::pair<int, int> destination(env.button.x, env.button.y);
                    std::pair<int, int> target = gui.getCamera().turnToViewSize(std::pair<int, int>(env.button.x, env.button.y));

                    int targetID = getTargetId(target);

                    gui.getCamera().setToViewSize(destination);

                    std::vector<int> selectedUnits = units.getSelectedUnits();

                    if (selectedUnits.size() > 0) {
                        if (targetID == -1) {
                            auto cMsgMover = std::make_shared<CMsgMover>(selectedUnits, destination);
                            queue.push(cMsgMover);
                        } else {
                            auto cMsgAtacar = std::make_shared<CMsgAtacar>(selectedUnits, targetID);
                            queue.push(cMsgAtacar);
                        }
                        sounds.playUnitAtack(0);
                    }
                }
                break;

            case SDL_MOUSEMOTION:

                if ((env.button.x > (this->window.GetWidth() - CAM_MOVEMENT_OFFSET)) && env.button.y < CAM_MOVEMENT_OFFSET) {
                    gui.getCamera().setDireccion(CAM_UR);
                } else if (env.button.x < CAM_MOVEMENT_OFFSET && env.button.y < CAM_MOVEMENT_OFFSET) {
                    gui.getCamera().setDireccion(CAM_UL);
                } else if (env.button.y > (this->window.GetHeight() - CAM_MOVEMENT_OFFSET) && (env.button.x > (this->window.GetWidth() - CAM_MOVEMENT_OFFSET))) {
                    gui.getCamera().setDireccion(CAM_DR);
                } else if (env.button.y > (this->window.GetHeight() - CAM_MOVEMENT_OFFSET) && env.button.x < CAM_MOVEMENT_OFFSET) {
                    gui.getCamera().setDireccion(CAM_DL);
                } else if (env.button.x < CAM_MOVEMENT_OFFSET) {
                    gui.getCamera().setDireccion(CAM_LEFT);
                } else if ((env.button.x > (this->window.GetWidth() - CAM_MOVEMENT_OFFSET))) {
                    gui.getCamera().setDireccion(CAM_RIGHT);
                } else if (env.button.y < CAM_MOVEMENT_OFFSET) {
                    gui.getCamera().setDireccion(CAM_UP);
                } else if (env.button.y > (this->window.GetHeight() - CAM_MOVEMENT_OFFSET)) {
                    gui.getCamera().setDireccion(CAM_DOWN);
                } else {
                    gui.getCamera().setDireccion(CAM_CENTER);
                }
                break;

            default:
                break;
        }
    }
}

void SDLgame::update() {
    gui.update();
    buildings.update(sounds);
    units.update(sounds);
}

void SDLgame::render() {
    map.render(gui);
    buildings.render(gui);
    units.render(gui);
    gui.render();
    renderEnergyAndMoney();
    renderMouse();
    renderWorm();
}

void SDLgame::renderEnergyAndMoney() {
    Texture text(renderer, font.RenderText_Solid("Energy: " + std::to_string(partida.getEnergy()) + " Money: " + std::to_string(partida.getMoney()),
                                                 SDL_Color{255, 255, 255, 255}));
    renderer.Copy(text, NullOpt, Rect(0, 0, text.GetWidth(), text.GetHeight()));
}

void SDLgame::renderMessage(std::string msg) {
    Texture text(renderer, font.RenderText_Solid(msg, SDL_Color{255, 255, 255, 255}));
    renderer.Copy(text, NullOpt, Rect(0, 0, window.GetWidth(), 300));
    Texture textq(renderer, font.RenderText_Solid("Press q to exit", SDL_Color{255, 255, 255, 255}));
    renderer.Copy(textq, NullOpt, Rect(0, window.GetHeight() * 0.5, window.GetWidth() * 0.5, window.GetHeight() * 0.2));
}

void SDLgame::select() {
    std::pair<int, int> cursor = gui.getCamera().turnToViewSize(std::pair<int, int>(selectFromX, selectFromY));

    buildings.removeSelected();
    units.removeSelected();

    for (auto &building : buildings.getBuildings()) {
        if (building->getPlayerID() == partida.getPlayerID())
            building->isClicked(cursor.first, cursor.second);
    }

    for (auto &unit : units.getUnits()) {
        if (unit->getPlayerID() == partida.getPlayerID()) {
            unit->isClicked(cursor.first, cursor.second, sounds);
        }
    }
}

void SDLgame::checkMultpleSelection(int x, int y) {
    std::pair<int, int> from = gui.getCamera().turnToViewSize(std::pair<int, int>(selectFromX, selectFromY));
    std::pair<int, int> to = gui.getCamera().turnToViewSize(std::pair<int, int>(x, y));

    buildings.removeSelected();
    units.removeSelected();

    for (auto &unit : units.getUnits()) {
        if (unit->getPlayerID() == partida.getPlayerID())
            unit->isClicked(from, to);
    }
    sounds.playUnitSelect(4);
}

int SDLgame::getTargetId(std::pair<int, int> position) {
    int unitID = units.getEnemyIdInPosition(position);
    if (unitID != -1) {
        return unitID;
    }
    int buildingID = buildings.getEnemyIdInPosition(position);
    if (buildingID != -1) {
        return buildingID;
    }
    return -1;
}

void SDLgame::renderMouse() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_ShowCursor(SDL_DISABLE);

    if (createBuilding != -1) {
        std::pair<int, int> dimensions = buildings.getBuildingDimension(createBuilding);
        bool canBuild = true;
        for (int i = 0; i < dimensions.first; i++) {
            for (int j = 0; j < dimensions.second; j++) {
                std::pair<int, int> cursor_pos(x / (CELL_SIZE * ZOOM) + i,
                                               y / (CELL_SIZE * ZOOM) + j);

                std::string color = map.getColorCanBuild((x + gui.getCamera().getX()) / (CELL_SIZE * ZOOM) + i,
                                                         (y + gui.getCamera().getY()) / (CELL_SIZE * ZOOM) + j);
                if (color == "red") {
                    canBuild = false;
                }

                if (color == "green") {
                    for (auto &build : buildings.getBuildings()) {
                        if (build->isInside(x + gui.getCamera().getX() + i * CELL_SIZE * ZOOM,
                                            y + gui.getCamera().getY() + j * CELL_SIZE * ZOOM)) {
                            color = "red";
                            canBuild = false;
                        }
                    }
                    for (auto &unit : units.getUnits()) {
                        if (unit->isInsideTile(x + gui.getCamera().getX() + i * CELL_SIZE * ZOOM,
                                               y + gui.getCamera().getY() + j * CELL_SIZE * ZOOM)) {
                            color = "red";
                            canBuild = false;
                        }
                    }
                }

                if (gui.getCamera().tileIsInside(cursor_pos)) {
                    renderer.Copy(
                        *textures[color],
                        Rect(0, 0, 16, 16),
                        Rect(x + i * CELL_SIZE * ZOOM,
                             y + j * CELL_SIZE * ZOOM,
                             CELL_SIZE * ZOOM,
                             CELL_SIZE * ZOOM));
                }
            }
        }
        createBuildingOK = canBuild;
    }

    if (units.getSelectedUnits().size() > 0) {
        renderer.Copy(
            *textures["cursor"],
            Rect(33 * (this->cursor++ % 8), 16, 33, 25),
            Rect(x - 16, y - 16, 32, 32));
    } else if (destroyBuilding) {
        renderer.Copy(
            *textures["cursor"],
            Rect(18 * (this->cursor++ % 8), 243, 18, 26),
            Rect(x - 8, y - 13, 32, 32));
    } else {
        renderer.Copy(
            *textures["cursor"],
            Rect(0, 0, 16, 16),
            Rect(x, y, 32, 32));
    }
}

void SDLgame::renderWorm() {
    bool isDifferent = false;
    std::pair<int, int> position = partida.getWorm().position;

    if (position != wormPosition) {
        isDifferent = true;
        wormPosition = position;
    }

    if (isDifferent || wormAttacking > 0) {
        wormAttacking = (wormAttacking + 1) % 16;

        renderer.Copy(
            *textures["worm" + std::to_string(wormAttacking)],
            Rect(0, 0,
                 textures["worm" + std::to_string(wormAttacking)]->GetWidth(),
                 textures["worm" + std::to_string(wormAttacking)]->GetHeight()),
            Rect(
                position.first * ZOOM - gui.getCamera().getX(),
                position.second * ZOOM - gui.getCamera().getY(),
                CELL_SIZE * ZOOM,
                CELL_SIZE * ZOOM));
    }
}

SDLgame::~SDLgame() {
    for (const auto &text : textures) {
        delete text.second;
    }
}
