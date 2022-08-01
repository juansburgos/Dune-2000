#ifndef CLIENT_SDL_BUILDINGS_SDLSPICESILO_H_
#define CLIENT_SDL_BUILDINGS_SDLSPICESILO_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "../common/defines.h"
#include "SDLbuilding.h"

using namespace SDL2pp;

class SDLSpiceSilo : public SDLbuilding {
   public:
    SDLSpiceSilo(StBuilding building, int house, YAML::Node data) : SDLbuilding(building, house, data){};

    virtual void render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) override;
};

#endif  // CLIENT_SDL_BUILDINGS_SDLSPICESILO_H_
