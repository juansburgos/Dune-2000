#include "SDLHeavyFactory.h"

void SDLHeavyFactory::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    renderer.Copy(
        *textures[std::to_string(type) + std::to_string(house) + std::to_string(getHealthImageID() + 1)],
        Rect(0, 0, 100, 100),
        Rect(
            position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderBuild(renderer, cam, textures);
    renderHealth(renderer, cam, textures);
    renderSelected(renderer, cam, textures);
}
