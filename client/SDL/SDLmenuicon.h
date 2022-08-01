#ifndef CLIENT_SDL_SDLMENUICON_H_
#define CLIENT_SDL_SDLMENUICON_H_

#include <SDL2pp/SDL2pp.hh>
#include <map>

#include "../common/defines.h"
#include "clases/YAMLbuilding.h"
#include "clases/YAMLunit.h"
#include "partida.h"
#include "yaml-cpp/yaml.h"

using namespace SDL2pp;

class SDLmenuicon {
    int minW, maxW, minH, maxH;
    int xi, xf, yi, yf;
    int type, self, house;
    int pos = 1;
    Partida &&partida;
    YAML::Node node;

    bool enPreparacion = false;
    bool preparado = false;
    bool available;
    std::vector<int> required;

    int costo, energy;

    int time = 0;

   public:
    SDLmenuicon(int windowWidth, int windowHeight, int house, int self, int type, Partida &partida, YAML::Node data);

    void render(Renderer &renderer, std::map<std::string, Texture *> &textures, int position);

    void update();
    void updateWindow(int windowWidth, int windowHeight, Partida &partida);

    void handleClick(int x, int y, int &createBuilding, int &createUnit);
    bool isInside(int x, int y);
    int getType();
};

#endif  // CLIENT_SDL_SDLMENUICON_H_
