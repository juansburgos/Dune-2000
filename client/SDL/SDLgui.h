#ifndef CLIENT_SDL_SDLGUI_H_
#define CLIENT_SDL_SDLGUI_H_

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "../common/defines.h"
#include "SDLcam.h"
#include "SDLmenu.h"
#include "partida.h"

using namespace SDL2pp;

class SDLgui {
    Window &window;
    Renderer &renderer;
    Partida &partida;
    SDLcam camera;
    SDLmenu menu;

   public:
    SDLgui(Window &wndw, Renderer &renderer, Partida &partida);

    SDLcam &getCamera();
    SDLmenu &getMenu();

    void render();
    void update();
};

#endif  // CLIENT_SDL_SDLGUI_H_
