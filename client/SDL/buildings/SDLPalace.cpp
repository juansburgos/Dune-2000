#include "SDLPalace.h"

void SDLPalace::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    float ww = 100;
    float hh = 109;
    float xx = ww * getHealthImageID();
    float yy = hh * house;

    if (house == 2) {
        hh = 114;
        yy = hh * house - 9;
        ww = ww - 5;
    }

    renderer.Copy(
        *textures["palace"],
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
