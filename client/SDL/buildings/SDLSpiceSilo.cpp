#include "SDLSpiceSilo.h"

void SDLSpiceSilo::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    renderer.Copy(
        *textures["silo"],
        Rect(33.2 + (getHealthImageID() * 3 * 33.2), house * 30.3, 33.2, 30.3),
        Rect(
            position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderBuild(renderer, cam, textures);
    renderHealth(renderer, cam, textures);
    renderSelected(renderer, cam, textures);
}
