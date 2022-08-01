#ifndef CLIENT_SDL_SDLGAME_H_
#define CLIENT_SDL_SDLGAME_H_

#include <SDL2pp/Font.hh>
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <utility>
#include <vector>

#include "SDLbuildings.h"
#include "SDLcam.h"
#include "SDLgui.h"
#include "SDLmap.h"
#include "SDLsound.h"
#include "SDLunits.h"
#include "clientqueue.h"
#include "cmsgatacar.h"
#include "cmsgconstruir.h"
#include "cmsgcrearunidad.h"
#include "cmsgdestruir.h"
#include "cmsgmover.h"
#include "partida.h"

using namespace SDL2pp;

class SDLgame {
    Window &window;
    Renderer &renderer;
    Texture &mapTexture;
    ClientQueue &queue;
    Partida &partida;
    SDLgui gui;
    SDLmap map;
    SDLunits units;
    SDLbuildings buildings;
    SDLsound sounds;
    Font font;
    bool is_running;
    bool createBuildingOK = true;
    int cursor = 0;
    int selectFromX = -1;
    int selectFromY = -1;
    int createUnit = -1;
    int createBuilding = -1;
    int wormAttacking = 0;
    std::pair<int, int> wormPosition;
    bool destroyBuilding = false;
    std::map<std::string, Texture *> textures;

   public:
    explicit SDLgame(Partida &partida, Window &window, Renderer &renderer, Texture &mapTexture, ClientQueue &queue);

    bool isRunning();

    void handleEvents();

    void render();

    void update();

    void renderEnergyAndMoney();

    void select();

    void checkMultpleSelection(int tox, int toy);

    int getTargetId(std::pair<int, int> position);

    void renderMouse();

    void renderWorm();

    void renderMessage(std::string msg);

    ~SDLgame();
};

#endif  // CLIENT_SDL_SDLGAME_H_
