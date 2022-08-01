#include "thdrawer.h"

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>
#include <utility>

#include "../common/defines.h"
#include "SDL.h"
#include "SDLgame.h"
#include "cmsgforcedend.h"

using namespace SDL2pp;

ThDrawer::ThDrawer(Partida &partida, ClientQueue &queue, bool& lostConn) : queue(std::move(queue)),
                                                                           partida(std::move(partida)),
                                                                           lostConnection(std::move(lostConn)) {
}

void ThDrawer::run() {
    SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDLTTF ttf;

    Window window("DUNE MAP",
                  SDL_WINDOWPOS_UNDEFINED,
                  SDL_WINDOWPOS_UNDEFINED,
                  WINDOW_INIT_WIDTH,
                  WINDOW_INIT_HEIGHT,
                  SDL_WINDOW_RESIZABLE);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Font font("../assets/SDL/ttf/Vera.ttf", 30);

    Texture text(renderer, font.RenderText_Solid("Waiting for other players", SDL_Color{255, 255, 255, 255}));

    int i = 0;
    while (partida.getTiles().size() == 0) {
        renderer.Clear();
        renderer.Copy(text, NullOpt, Rect(0, i % window.GetHeight(), window.GetWidth(), 300));
        renderer.Present();
        SDL_Delay(1000 / FPS_CLIENT);
        i++;
    }

    Texture mapTexture(renderer, "../assets/bloxbgbs.png");

    SDLgame game(partida, window, renderer, mapTexture, queue);

    while (game.isRunning() && !lostConnection) {
        Uint32 frameStart = SDL_GetTicks();
        renderer.Clear();

        if (partida.getIsRunning() && !partida.getHasLost()) {
            game.update();
            game.handleEvents();
            game.render();
        } else {
            if (partida.getHasLost())
                game.renderMessage("perdiste");
            else
                game.renderMessage("ganaste");
            game.handleEvents();
        }
        renderer.Present();

        Uint32 frameEnd = SDL_GetTicks();
        Uint32 processTime = frameEnd - frameStart;

        if (1000 / FPS_CLIENT > processTime)
            SDL_Delay(1000 / FPS_CLIENT - processTime);
        else
            std::cout << "Frame Rate Muy Elevado !!!" << std::endl;
    }
    partida.endGame();
    auto cMsgEnd = std::make_shared<CMsgForcedEnd>();
    queue.push(cMsgEnd);
}
