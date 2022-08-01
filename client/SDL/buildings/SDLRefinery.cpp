#include "SDLRefinery.h"

void SDLRefinery::render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) {
    YAMLbuilding Ybuilding(node, type);

    std::pair<int, int> tamanio = Ybuilding.getDimensions();

    float xN = 0.2;
    float yN = 0.9;

    int destruido = getHealthImageID();

    if (destruido) {
        if (house == 2) {
            yN = 0.55;
        } else if (house == 1) {
            yN = 0.75;
            xN = 0.15;
        }
    } else {
        if (house == 1) {
            xN = 0.15;
            yN = 0.85;
        }
    }

    renderer.Copy(
        *textures["4" + std::to_string(house) + std::to_string(0)],
        Rect(0, 0,
             textures["4" + std::to_string(house) + std::to_string(0)]->GetWidth(),
             textures["4" + std::to_string(house) + std::to_string(0)]->GetHeight()),
        Rect(
            position.first - cam.getX(),
            position.second - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderer.Copy(
        *textures["4" + std::to_string(house) + std::to_string(destruido + 1)],
        Rect(0, 0,
             textures["4" + std::to_string(house) + std::to_string(destruido + 1)]->GetWidth(),
             textures["4" + std::to_string(house) + std::to_string(destruido + 1)]->GetHeight()),
        Rect(
            position.first + xN - cam.getX(),
            position.second - yN - cam.getY(),
            cam.turnToViewSize(tamanio.first),
            cam.turnToViewSize(tamanio.second)));

    renderBuild(renderer, cam, textures);
    renderHealth(renderer, cam, textures);
    renderSelected(renderer, cam, textures);
}
