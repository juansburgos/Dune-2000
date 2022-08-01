#ifndef CLIENT_SDL_BUILDINGS_SDLREFINERY_H_
#define CLIENT_SDL_BUILDINGS_SDLREFINERY_H_

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#include "../common/defines.h"
#include "SDLbuilding.h"

using namespace SDL2pp;

class SDLRefinery : public SDLbuilding {
   public:
    SDLRefinery(StBuilding &building, int house, YAML::Node data) : SDLbuilding(building, house, data){};

    virtual void render(Renderer &renderer, SDLcam &cam, std::map<std::string, Texture *> &textures) override;
};

#endif  // CLIENT_SDL_BUILDINGS_SDLREFINERY_H_
