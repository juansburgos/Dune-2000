#ifndef CLIENT_SDL_SDLMENU_H_
#define CLIENT_SDL_SDLMENU_H_

#include <SDL2pp/SDL2pp.hh>
#include <map>

#include "../common/defines.h"
#include "SDLmenuicon.h"
#include "clases/YAMLbuilding.h"
#include "partida.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLmenu {
    int minW, maxW, minH, maxH, house;
    std::vector<SDLmenuicon> units;
    std::vector<SDLmenuicon> buildings;
    YAML::Node yamlAssets;

    int initBuildings = 0;
    int initUnits = 0;

    Renderer &renderer;
    std::map<std::string, Texture *> textures;

   public:
    SDLmenu(int windowWidth, int windowHeight, int house, Renderer &renderer, Partida &partida);

    void render();
    void renderHouseIcon();
    void renderBuildings();
    void renderUnits();

    void update();

    void update(int windowWidth, int windowHeight, Partida &partida);

    void handleClick(int x, int y, int &createBuilding, int &createUnit, bool &destroyBuilding);

    ~SDLmenu();
};

#endif  // CLIENT_SDL_SDLMENU_H_
