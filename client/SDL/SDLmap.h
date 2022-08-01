#ifndef CLIENT_SDL_SDLMAP_H_
#define CLIENT_SDL_SDLMAP_H_

#include <SDL2pp/SDL2pp.hh>
#include <utility>
#include <vector>

#include "SDLcam.h"
#include "SDLgui.h"
#include "partida.h"

using namespace SDL2pp;

class SDLmap {
    Partida &&partida;
    Renderer &renderer;
    Texture &texture;

    std::vector<std::vector<int>> tiles;
    std::vector<std::vector<int>> spices;

    void setTiles(std::vector<std::vector<int>> tiles);

    void setSpices(std::vector<std::vector<int>> spices);

    void renderTiles(SDLgui &gui);

    void renderSpices(SDLgui &gui);

    void renderTerrain(SDLgui &gui);

    std::vector<int> tileType = TILETYPE_TYPE;

   public:
    explicit SDLmap(Partida &partida, Renderer &renderer, Texture &texture);

    int getTileType(std::pair<int, int> position);

    int getSpiceType(std::pair<int, int> position);

    void render(SDLgui &gui);

    std::string getColorCanBuild(int x, int y);
};

#endif  // CLIENT_SDL_SDLMAP_H_
