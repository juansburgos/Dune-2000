#include "SDLAirTrap.h"

void SDLAirTrap::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    float ww = (house == 0) ? 63 : 64;
    float hh = 75;
    float xx = ww * getHealthImageID();
    float yy = (399 / 3) * house + (house == 2 ? 4 : 1);

    renderer.Copy(
        *textures["AirTrap"],
        Rect(xx, yy, ww, hh),
        Rect(
            position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderBuild(renderer, cam, textures);
    renderHealth(renderer, cam, textures);
    renderSelected(renderer, cam, textures);
}
