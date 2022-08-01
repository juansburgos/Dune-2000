#include "SDLLightFactory.h"

void SDLLightFactory::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    float ww = 282 / 3;
    float hh = 190 / 3;
    float xx = ww * (getHealthImageID() + 1);
    float yy = hh * house;

    renderer.Copy(
        *textures["LFactory"],
        Rect(xx, yy, ww, hh),
        Rect(
            position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderer.Copy(
        *textures["LFactory"],
        Rect(0, yy, ww, hh),
        Rect(
            0.22 + position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderBuild(renderer, cam, textures);
    renderHealth(renderer, cam, textures);
    renderSelected(renderer, cam, textures);
}
