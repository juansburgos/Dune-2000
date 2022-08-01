#include "SDLgui.h"

using namespace SDL2pp;

SDLgui::SDLgui(Window &wndw, Renderer &renderer, Partida &partida) : camera(wndw.GetWidth() * GUI_MAP_WIDTH, wndw.GetHeight(), partida),
                                                                     window(wndw),
                                                                     renderer(renderer),
                                                                     partida(partida),
                                                                     menu(wndw.GetWidth(), wndw.GetHeight(), partida.getHouse(), renderer, partida) {}

void SDLgui::update() {
    camera.updateWindow(window.GetWidth() * GUI_MAP_WIDTH, window.GetHeight());
    camera.update();
    menu.update(window.GetWidth(), window.GetHeight(), partida);
}

void SDLgui::render() {
    menu.render();
    menu.renderHouseIcon();
    menu.renderBuildings();
    menu.renderUnits();
}

SDLcam &SDLgui::getCamera() {
    return camera;
}

SDLmenu &SDLgui::getMenu() {
    return menu;
}
